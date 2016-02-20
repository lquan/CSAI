/*
 *  Main authors:
 *      Tias Guns <tias.guns@cs.kuleuven.be>
 *      Siegfried Nijssen <siegfried.nijssen@cs.kuleuven.be>
 *
 *  Copyright:
 *      Tias Guns, 2008
 *      Siegfried Nijssen, 2011
 *
 *  Revision information:
 *      $Id: graph_cp.cc 128 2008-08-07 11:23:23Z tias $
 *
 *  This file is part of Graph_cp and uses Gecode.
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
#ifndef ITEMSET_HH
#define ITEMSET_HH
#include <stdio.h>
#include <vector>
#include <gecode/kernel.hh>
#include <gecode/int.hh>
#include <gecode/iter.hh>
#include <gecode/int/rel.hh>
#include "regression.hh"

using namespace std;
using namespace Gecode;
using namespace Gecode::Int;

  /// Information stored for an itemset during the search
struct Ritemset {
  public:
    // Next pointer
    Ritemset* next;
    // Items of this point
    const vector<bool> items;
    // Transactions of this point
    const vector<bool> trans;
    Ritemset_Stat stat; 

    // Constructor
    Ritemset(vector<bool> items0, vector<bool> trans0, const Ritemset_Stat &stat):
        items(items0), trans(trans0),
        stat(stat) {
        next = NULL;
    }
    // Phony for skipping const of print function where we have to add
    Ritemset(): items(NULL), trans(NULL) {
        next = NULL;
    }

    inline void print(FILE* solfile) {
        for (unsigned int i=0; i!=items.size(); i++) {
            if (items[i])
                fprintf(solfile, "%i ", i);
        }
        //fprintf(solfile, "(%i:+%i-%i) [%.5f], score is %i\n", pos+neg,pos,neg, value, score);
        fprintf(solfile, "(%i:%f) [%.5f]\n", stat.tot, stat.prediction, stat.value);
    }

    inline void print_full(FILE* solfile) {
        for (unsigned int i=0; i!=items.size(); i++) {
            if (items[i])
                fprintf(solfile, "%i ", i);
        }
        fprintf(solfile, " < " );
        for (unsigned int t=0; t!=trans.size(); t++) {
            if (trans[t])
                fprintf(solfile, "%i ", t);
        }
        fprintf(solfile, ">\n");
    }
};


#endif
