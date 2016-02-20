/*
 *  Main authors:
 *      Tias Guns <tias.guns@cs.kuleuven.be>
 *      Siegfried Nijssen <siegfried.nijssen@cs.kuleuven.be>
 *
 *  Copyright:
 *      Tias Guns, 2008
 *      Siegfried Nijssen, 2011
 *
 *  This file is part of Cimcp, Correlated Itemset Mining using
 *  Constraint Programming, and uses Gecode.
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
// lot's of duplicate code with cimcp_Fconvex, but because of the way run() is called in the constructor, inheriting from it is not straightforward

#include "common/fimcp_basic.hh"
#include "common/itemset.hh"
#include "common/constraint_regression.hh" // regression constraints

#define PRECISION 100000

/// TO IMPLEMENT ADDITIONAL CONSTRAINTS IN THE MODEL, EXTEND THE Model_Regression::run FUNCTION!

/**
 * Itemset mining wrt a regression function
 * inherits from Fimcp_basic.
 */
class Model_Regression : public Fimcp_basic {
protected:
  /// minimum score; is converted from floats by means of the PRECISION constant
  IntVar score;

  /// top-k itemsets (is linked list struct, with filler first)
  Ritemset* itemsets;

  /// k, nr of top itemsets to mine
  int k;

public:
    Model_Regression (const Options_fimcp& opt) :
        Fimcp_basic(opt) {
        // have to set filler first, otherwise we cannot
        // add items in the const print() function.
        Ritemset* filler = new Ritemset();
        itemsets = filler;

        run(opt);
    }

    Model_Regression (bool share, Model_Regression& s) :
        Fimcp_basic(share, s) {
        score.update(*this, share, s.score);
        itemsets = s.itemsets;
        k = s.k;
    }

    /// Perform copying during cloning
    virtual Space* copy(bool share) {
      return new Model_Regression (share,*this);
    }

    /// Add constraint for next better solution
    virtual void constrain(const Space&) {
        // constrain() is called after print()
        // we add the itemset to the topk in print()
        // because constrain() is never called for the last item

        // set the treshold wrt. itemset k
        Ritemset* last = itemsets;
        while (last->next != NULL)
            last = last->next;
        rel(*this, score, IRT_LE, last->stat.value * PRECISION );
    }

    virtual void run(const Options_fimcp& opt);

    /// Print solution
    virtual void print(std::ostream&) const;

    /// Construct PNitemset from current solution (has to be const because print is)
    virtual Ritemset* constructRitemset() const;

    /// add itemset to the topk solutions (has to be const because print is)
    virtual void addItemset(Ritemset* cur) const;
};



/// CHANGE THIS FUNCTION IF YOU WISH TO ADD CONSTRAINTS
void Model_Regression ::run(const Options_fimcp& opt) {
    setRegression ( opt.regressionMeasure() );

    const vector< vector<bool> > tdb = common_construction(opt);
    if (labels->size() == 0)
        throw Exception("Regression label error", "no regression labels found");
    // number of top-k itemsets
    k = opt.alpha();

    /** covered constraints **/
    if (opt.cclause()) {
        // Default! Clause is a bit faster and uses less memory
        coverage_clause(tdb);
    } else {
        IntArgs row_(nr_i);
        for (int t=0; t!=nr_t; t++) {
            // make 1-row
            for (int i=0; i!=nr_i; i++)
                row_[i] = (1-tdb[t][i]);

            // coverage: the trans its complement has no supported items
            // sum((1-row(trans_t))*Items) = 0 <=> trans_t
            linear(*this, row_, items, IRT_EQ, 0, transactions[t]);
        }
    }

    /** closed constraints **/
    {
        IntArgs col_(nr_t);
        for (int i=0; i!=nr_i; i++) {
            // make 1-col
            for (int t=0; t!=nr_t; t++)
                col_[t] = (1-tdb[t][i]);

            // closed: the item its complement has no supported trans
            // sum((1-col(item_i))*Trans) = 0 <=> item_i
            linear(*this, col_, transactions, IRT_EQ, 0, items[i]);
        }
    }

    /** regression function constraint, of which the implementation needs to be finished **/
    {
        // convert treshold to integer, default: [min*PRECISION, _MAX]
        score = IntVar(*this, Gecode::Int::Limits::min, (int)(opt.delta()*PRECISION) );

        // for every item separately (reified, allows iterative pruning)
        for (int i=0; i!=nr_i; i++) {
            // count cols
            BoolVarArgs cols ( nr_t );
            int cnt = 0;
            for (int t=0; t!=nr_t; t++) 
              cols[cnt++] = transactions[t];

            Constraint_Regression::imply_regression(*this, items[i], cols, labels, IRT_LQ, score, PRECISION);
        }
    }

    /** size constraint **/
    // size: the size of the itemset is within the bound
    // count(items) >=< X  [>=<:{>=,=<,=,!=,<,>}, X:integer]
    //linear(*this, items, (IntRelType)opt.bound1_op(), opt.bound1_val());


    // avoid empty itemset -> size constraint??
    linear(*this, items, IRT_GQ, 1);
    
    /** search **/
    branch(*this, items, (IntVarBranch)opt.branching(), (IntValBranch)opt.branchval());
}



/// THE FUNCTIONS BELOW DO NOT NEED TO BE CHANGED - THEY ARE THERE ONLY TO HELP

/// Construct PNitemset from current solution
inline Ritemset* Model_Regression::constructRitemset() const {
    vector<bool> curItems(nr_i);
    for (int i = 0; i!=nr_i; i++) 
        curItems[i] = items[i].val();
    vector<bool> curTrans(nr_t);
    for ( int t = 0; t != nr_t; t++ ) 
        curTrans[t] = transactions[t].val ();
           

    Ritemset_Stat stat = statRegression ( transactions, *labels );
        
    return new Ritemset( curItems, curTrans, stat );
}

/// Print solution
void Model_Regression::print(std::ostream& os) const {
    // print() is called before constrain()
    // we add the itemset here because constrain() is never called for the last item
    // this function is const so our first itemset is a filler

    if (print_itemsets == PRINT_CPVARS) {
        // Output CP variables (usually for GIST)
        os << "Only printing current solution:\n";
        os << "\tscore = " << score << std::endl;
        os << "\tI[] = " << items << std::endl;
        os << "\tT[] = " << transactions << std::endl;
        // if not all vars assigned (partial solution printed in GIST),
        // return here
        bool all_assigned = true;
        for (int i = 0; i!=nr_i && all_assigned; i++)
            all_assigned &= items[i].assigned();
        for (int t = 0; t!=nr_t && all_assigned; t++)
            all_assigned &= transactions[t].assigned();
        if (!all_assigned)
            return;
    }

    if (k == 0) { // top-0: all (but none in memory)
        if (print_itemsets == PRINT_NONE)
            return;
    
        Ritemset* cur = constructRitemset();

        if (print_itemsets == PRINT_FIMI) {
            cur->print(solfile);
        } else if (print_itemsets == PRINT_FULL) {
            cur->print_full(solfile);
        } else if (print_itemsets == PRINT_CPVARS) {
            cur->print(stdout);
        }

        delete cur;

    } else { // top-k (keep k in memory)
        Ritemset* cur = constructRitemset();
        addItemset(cur);

        if (print_itemsets == PRINT_NONE) {
            return;
        } else if (print_itemsets == PRINT_FIMI) {
            // print entire patternset
            Ritemset* iter = itemsets;
            while (iter->next != NULL) {
                iter = iter->next; // skip first filler
                iter->print(solfile);
            }
        } else if (print_itemsets == PRINT_FULL) {
            // print entire patternset
            Ritemset* iter = itemsets;
            while (iter->next != NULL) {
                iter = iter->next; // skip first filler
                iter->print_full(solfile);
            }
        } else if (print_itemsets == PRINT_CPVARS) {
            // also print normal output, but on stdout
            Ritemset* iter = itemsets;
            while (iter->next != NULL) {
                iter = iter->next; // skip first filler
                iter->print(stdout);
            }
        }
    }
}

/// add itemset to the topk solutions
inline void Model_Regression::addItemset(Ritemset* cur) const {
    if (k == 0)
        return;

    Ritemset* prev = itemsets;
    int count = 0;
    while (prev->next != NULL &&
            prev->next->stat.value <= cur->stat.value ) {
        prev = prev->next;
        count++;
    }

    cur->next = prev->next;
    prev->next = cur;
    count++;

    while (prev->next != NULL &&
            count <= k) {
        prev = prev->next;
        count++;
    }

    // clean up
    delete prev->next;
    prev->next = NULL;

    if (print_itemsets != PRINT_NONE)
        fprintf(stdout, "\tAdded itemset, min value=%.5f:\n", prev->stat.value);
    return;
}
