/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Mikael Lagerkvist <lagerkvist@gecode.org>
 *
 *  Copyright:
 *     Mikael Lagerkvist, 2006
 *
 *  Last modified:
 *     $Date: 2010-10-07 11:52:01 +0200 (Thu, 07 Oct 2010) $ by $Author: schulte $
 *     $Revision: 11473 $
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <gecode/driver.hh>
#include <gecode/int.hh>

#include <vector>
#include <algorithm>
#include <sstream>

using namespace Gecode;

namespace {
  using std::vector;

  /// Layout of the cards
  vector<vector<int> > layout;
  /// information for locating particular cards in the layout
  vector<int> layer, pile;

  /** \brief Generates\ref layout.
   *
   * This function generates the layeout and intializes \ref layer and
   * \ref pile from it. The layout is randomly generated from the
   * supplied seed.
   */
  void generate(int seed) {
    // The layout consists of 17 piles of 3 cards each
    layout = vector<vector<int> >(17, vector<int>(3));
    // Deck without the Ace of Spades
    vector<int> deck(51);
    for (int i = 51; i--; ) deck[i] = i+1;
    Support::RandomGenerator rnd(seed+1);
    std::random_shuffle(deck.begin(), deck.end(), rnd);

    // Place cards from deck
    int pos = 0;
    for (int i = 17; i--; )
      for (int j = 3; j--; )
        layout[i][j] = deck[pos++];

    // Location-information for each card
    layer = vector<int>(52);
    pile  = vector<int>(52);
    for (int i = 17; i--; ) {
      for (int j = 3; j--; ) {
        layer[layout[i][j]] = j;
        pile[ layout[i][j]] = i;
      }
    }
  }
}



/** \brief Custom brancher for black hole patience
 *
 * This class implements a custom brancher for BlackHole that
 * instantiates the variables in lexical order, and chooses the value
 * with the most cards under it.
 *
 * \relates BlackHole
 */
class BlackHoleBranch : Brancher {
protected:
  /// Views of the brancher
  ViewArray<Int::IntView> x;
  /// Cache of first unassigned variable
  mutable int start;
  /// %Choice for black hole brancher
  class Choice : public Gecode::Choice {
  public:
    /// Position of variable
    int pos;
    /// Value of variable
    int val;
    /** Initialize description for brancher \a b, position \a pos0, 
     *  and value \a val0.
     */
    Choice(const Brancher& b, int pos0, int val0)
      : Gecode::Choice(b,2), pos(pos0), val(val0) {}
    /// Report size occupied
    virtual size_t size(void) const {
      return sizeof(Choice);
    }
  };

  /// Construct brancher
  BlackHoleBranch(Home home, ViewArray<Int::IntView>& xv)
    : Brancher(home), x(xv), start(0) {}
  /// Copy constructor
  BlackHoleBranch(Space& home, bool share, BlackHoleBranch& b)
    : Brancher(home, share, b), start(b.start) {
    x.update(home, share, b.x);
  }

public:
  /// Check status of brancher, return true if alternatives left.
  virtual bool status(const Space&) const {
    for (int i = start; i < x.size(); ++i)
      if (!x[i].assigned()) {
        start = i;
        return true;
      }
    // No non-assigned orders left
    return false;
  }
  /// Return choice
  virtual Choice* choice(Space&) {
    int val = -1;
    int w = 4;
    for (Int::ViewValues<Int::IntView> vals(x[start]); vals(); ++vals)
      if (layer[vals.val()] < w) {
        val = vals.val();
        if ((w = layer[vals.val()]) == 0) break;
      }

    assert(val >= 1 && val < 52);
    return new Choice(*this, start, val);
  }
  /// Perform commit for choice \a _c and alternative \a a.
  virtual ExecStatus commit(Space& home, const Gecode::Choice& _c,
                            unsigned int a) {
    const Choice& c = static_cast<const Choice&>(_c);
    if (a)
      return me_failed(x[c.pos].nq(home, c.val)) ? ES_FAILED : ES_OK;
    else
      return me_failed(x[c.pos].eq(home, c.val)) ? ES_FAILED : ES_OK;
  }
  /// Copy brancher
  virtual Actor* copy(Space& home, bool share) {
    return new (home) BlackHoleBranch(home, share, *this);
  }
  /// Post brancher
  static void post(Home home, IntVarArgs x) {
    ViewArray<Int::IntView> xv(home, x);
    (void) new (home) BlackHoleBranch(home, xv);
  }
  /// Delete brancher and return its size
  virtual size_t dispose(Space&) {
    return sizeof(*this);
  }
};


/**
 * \brief %Example: Black hole patience
 *
 * This example solves instances of the black-hole patience game.
 *
 * The model of the problem is mostly taken from "Search in the
 * Patience Game 'Black Hole'", by Ian P. Gent, Chris Jefferson, Tom
 * Kelsey, In�s Lynce, Ian Miguel, Peter Nightingale, Barbara
 * M. Smith, and S. Armagan Tarim.
 *
 * The conditional symmetry identified in the above paper can be
 * eliminated (enabled by default).
 *
 * \ingroup Example
 *
 */
class BlackHole : public Script {
protected:
  IntVarArray x, ///< Card at position
    y; ///< Position of card

  /// Return a string representing the card of value val
  std::string
  card(int val) const {
    const char* suit = "SCHD";
    std::ostringstream o;
    o << std::setw(2) << (1 + (val%13)) << suit[val/13];
    return o.str();
  }

public:
  /// Symmetry variants
  enum {
    SYMMETRY_NONE,       ///< No symmetry breaking
    SYMMETRY_CONDITIONAL ///< Breaking conditional symmetries
  };
  /// Propagation of placement-rules
  enum {
    PROPAGATION_REIFIED,  ///< Reified propagation
    PROPAGATION_DFA,      ///< Extensional propagation using automatons
    PROPAGATION_TUPLE_SET ///< Extensional propagation using tables
  };
  /// Actual model
  BlackHole(const SizeOptions& opt)
    : x(*this, 52, 0,51), y(*this, 52, 0,51)
  {
    // Black ace at bottom
    rel(*this, x[0], IRT_EQ, 0);

    // x is order and y is placement
    channel(*this, x, y, opt.icl());

    // The placement rules: the absolute value of the difference
    // between two consecutive cards is 1 or 12.
    if (opt.propagation() == PROPAGATION_REIFIED) {
      // Build table for accessing the rank of a card
      IntArgs modtable(52);
      for (int i = 0; i < 52; ++i) {
        modtable[i] = i%13;
      }
      for (int i = 0; i < 51; ++i) {
        IntVar x1(*this, 0, 12), x2(*this, 0, 12);
        element(*this, modtable, x[i], x1);
        element(*this, modtable, x[i+1], x2);
        const int dr[2] = {1, 12};
        IntVar diff(*this, IntSet(dr, 2));
        rel(*this, abs(x1-x2) == diff, ICL_DOM);
      }
    } else if (opt.propagation() == PROPAGATION_DFA) {
      // Build table for allowed tuples
      REG expression;
      for (int r = 13; r--; ) {
        for (int s1 = 4; s1--; ) {
          for (int s2 = 4; s2--; ) {
            for (int i = -1; i <= 1; i+=2) {
              REG r1 = REG(r+13*s1);
              REG r2 = REG((r+i+52+13*s2)%52);
              REG r = r1 + r2;
              expression |= r;
            }
          }
        }
      }
      DFA table(expression);

      for (int i = 51; i--; )
        extensional(*this, IntVarArgs() << x[i] << x[i+1], table);

    } else { // opt.propagation() == PROPAGATION_TUPLE_SET)
      // Build table for allowed tuples
      TupleSet tupleSet;
      for (int r = 13; r--; )
        for (int s1 = 4; s1--; )
          for (int s2 = 4; s2--; )
            for (int i = -1; i <= 1; i+=2) {
              tupleSet.add(IntArgs(2, r+13*s1, (r+i+52+13*s2)%52));
            }
      tupleSet.finalize();

      for (int i = 51; i--; )
        extensional(*this, IntVarArgs() << x[i] << x[i+1], tupleSet);
    }

    // A card must be played before the one under it.
    for (int i = 17; i--; )
      for (int j = 2; j--; )
        rel(*this, y[layout[i][j]] < y[layout[i][j+1]]);

    // Compute and break the conditional symmetries that are dependent
    // on the current layout.
    // Two cards with the same rank but different suits are symmetric
    // with respect to their placement in the black hole if changing
    // their order does not affect any other card.
    if (opt.symmetry() == SYMMETRY_CONDITIONAL) {
      // For all ranks
      for (int r = 13; r--; ) {
        // For all pairs of suits
        for (int s1 = 4; s1--; ) {
          for (int s2 = s1; s2--; ) {
            int c1 = 13*s1 + r,
              c2 = 13*s2 + r;
            // The ace of spades is already placed
            if (c1 == 0 || c2 == 0) continue;
            // Piles are handled by the rules of the game
            if (pile[c1] == pile[c2]) continue;
            // Fix the right order of the cards
            int o1 = c1, o2 = c2;
            if (pile[c1] > pile[c2] && layer[c2] >= layer[c1])
              std::swap(o1, o2);
            // cond is the condition for the symmetry
            BoolVarArgs ba;
            // Both cards played after the ones on top of them
            for (int i = 0; i < layer[o1]; ++i)
              ba << expr(*this, (y[layout[pile[o1]][i]] < y[o2]));
            for (int i = 0; i < layer[o2]; ++i)
              ba << expr(*this, (y[layout[pile[o2]][i]] < y[o1]));
            // Both cards played before the ones under them
            for (int i = layer[o1]+1; i < 3; ++i)
              ba << expr(*this, (y[o2] < y[layout[pile[o1]][i]]));
            for (int i = layer[o2]+1; i < 3; ++i)
              ba << expr(*this, (y[o1] < y[layout[pile[o2]][i]]));
            // Cond holds when all the above holds
            BoolVar cond(*this, 0, 1);
            rel(*this, BOT_AND, ba, cond);

            // If cond is fulfilled, then we can order the cards
            // cond -> (y[o1] < y[o2])
            rel(*this, !cond || (y[o1] < y[o2]));
          }
        }
      }
    }

    // Install custom brancher
    BlackHoleBranch::post(*this, x);
  }

  /// Print instance and solution
  virtual void
  print(std::ostream& os) const {
    os << "Layout:" << std::endl;
    for (int i = 0; i < 17; i++) {
      for (int j = 0; j < 3; j++)
        os << card(layout[i][j]) << " ";
      if ((i+1) % 3 == 0)
        os << std::endl;
      else
        os << "  \t";
    }
    os << std::endl << std::endl;

    os << "Solution:" << std::endl;
    for (int i = 0; i < 52; ++i) {
      if (x[i].assigned())
        os << card(x[i].val()) << " ";
      else
        os << "   ";
      if ((i + 1) % 13 == 0)
        os << std::endl;
    }
    os << std::endl;
    os << std::endl;
  }

  /// Constructor for cloning \a s
  BlackHole(bool share, BlackHole& s) : Script(share,s) {
    x.update(*this, share, s.x);
    y.update(*this, share, s.y);
  }
  /// Copy during cloning
  virtual Space*
  copy(bool share) {
    return new BlackHole(share,*this);
  }
};

/** \brief Main-function
 *  \relates BlackHole
 */
int
main(int argc, char* argv[]) {
  SizeOptions opt("Black Hole patience");
  opt.symmetry(BlackHole::SYMMETRY_CONDITIONAL);
  opt.symmetry(BlackHole::SYMMETRY_NONE,"none",
               "no symmetry breaking");
  opt.symmetry(BlackHole::SYMMETRY_CONDITIONAL,"conditional",
               "break conditional symmetries");
  opt.propagation(BlackHole::PROPAGATION_DFA);
  opt.propagation(BlackHole::PROPAGATION_REIFIED,
                  "reified", "use reified propagation");
  opt.propagation(BlackHole::PROPAGATION_DFA,
                  "dfa", "use DFA-based extensional propagation");
  opt.propagation(BlackHole::PROPAGATION_TUPLE_SET,
                  "tuple-set", "use TupleSet-based extensional propagation");
  opt.icl(ICL_DOM);
  opt.parse(argc,argv);
  // Generates the new board
  generate(opt.size());
  Script::run<BlackHole,DFS,SizeOptions>(opt);
  return 0;
}

// STATISTICS: example-any
