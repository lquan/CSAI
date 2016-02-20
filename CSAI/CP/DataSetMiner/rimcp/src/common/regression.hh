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
#ifndef REGRESSION_HH
#define REGRESSION_HH
#include <stdio.h>
#include <vector>
#include <gecode/int.hh>
#include <gecode/kernel.hh>
#include <gecode/iter.hh>
#include <gecode/int/rel.hh>

using namespace std;
using namespace Gecode;
using namespace Gecode::Int;

// statistics stored for this itemset in the top-k set of itemsets during the search
struct Ritemset_Stat {
    // Number of transactions covered
    int tot;
    // prediction for this itemset
    float prediction;
    // actual value of evaluation function (no PRECISION)
    float value;
};


// The functions below are there to allow multiple regression algorithms by simply linking
// additional objects in the binary.

typedef Ritemset_Stat (*statRegressionType) ( const BoolVarArray &transactions, const vector<float> &labels );
typedef bool (*propagateRegressionType) ( const ViewArray<BoolView> &transactions, const vector<float> &labels, float value );


class InitRegressionHelp {
  private:
    friend void ::setRegression ( const char *name );
    friend const char *::defaultRegression ();
    static InitRegressionHelp *first;
    statRegressionType statRegression;
    propagateRegressionType propagateRegression;
    char *name;
    InitRegressionHelp *next;
  public:
    
    InitRegressionHelp ( const char *name, statRegressionType statRegression, propagateRegressionType propagateRegression ):
      statRegression( statRegression ),
      propagateRegression ( propagateRegression ),
      name ( strdup ( name ) ) {
        next = first;
        first = this;
    }
};

#define registerRegression(name,statR,propagateR) InitRegressionHelp init##statR##propagateR(name,statR,propagateR)

void setRegression ( const char *name );
const char *defaultRegression ();

extern statRegressionType statRegression;
extern propagateRegressionType propagateRegression;


#endif
