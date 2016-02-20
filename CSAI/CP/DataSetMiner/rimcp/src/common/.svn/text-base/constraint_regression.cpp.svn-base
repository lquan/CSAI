/*
 *  Main authors:
 *      Tias Guns <tias.guns@cs.kuleuven.be>
 *      Siegfried Nijssen <siegfried.nijssen@cs.kuleuven.be>
 *
 *  Copyright:
 *      Tias Guns, 2008
 *      Siegfried Nijssen, 2011
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
#include "constraint_regression.hh"
#include "itemset.hh"
#include "regression.hh"


namespace Constraint_Regression {

  RegressionLe::RegressionLe(Space& home, ViewArray<BoolView> &cols, vector<float> *labels, IntView c, int precision )
    :  Propagator(home), cols(cols), c(c), precision(precision), labels(labels) {
    cols.subscribe(home,*this,PC_INT_VAL);
    c.subscribe(home,*this,PC_INT_BND);
  }

  forceinline size_t
  RegressionLe::dispose(Space& home) {
    assert(!home.failed());
    cols.cancel(home,*this,PC_INT_VAL);
    c.cancel(home,*this,PC_INT_BND);
    (void) Propagator::dispose(home);
    return sizeof(*this);
  }

  forceinline
  RegressionLe::RegressionLe(Space& home,
            bool share, RegressionLe& p)
    : Propagator(home,share,p), cols(p.cols), c(p.c), precision(p.precision), labels(p.labels) {
    cols.update(home,share,p.cols);
    c.update(home,share,p.c);
  }

  PropCost
  RegressionLe::cost(const Space&, const ModEventDelta&) const {
    return PropCost::linear(PropCost::LO, cols.size());
  }

  ExecStatus
  RegressionLe::post(Space& home, ViewArray<BoolView> &cols, vector<float> *labels, IntView c, int precision) {
    (void) new (home) RegressionLe(home,cols, labels,c,precision);
    return ES_OK;
  }

  Actor*
  RegressionLe::copy(Space& home, bool share) {
    return new (home) RegressionLe(home,share,*this);
  }

  ExecStatus
  RegressionLe::propagate(Space& home, const ModEventDelta&) {
    
    bool reach = propagateRegression ( cols, *labels, c.max () / (float) precision );
    
    // maximum of monotone function must be greater or equal than treshold
    if ( reach ) {
        if ( cols.assigned () )
            return home.ES_SUBSUMED(*this);
        return ES_FIX;
    }
    else
        return ES_FAILED;
  }
  
  /** \brief Post propagator for the regression propagator
   *
   */
  void regressionle(Space& home, const BoolVarArgs &cols, vector<float> *labels,
                    IntRelType r, IntVar c, int precision) {
    if (home.failed()) return;

    if (r == IRT_LQ) {
        ViewArray<BoolView> cols0(home,cols);
        GECODE_ES_FAIL((RegressionLe
                             ::post(home, cols0, labels, c, precision)));
    } else {
      throw UnknownRelation("RegressionLe::regressionle");
    }
  }




  /************************************
   *      REIFY-IMPLIED               *
   ***********************************/

  ImplyRegressionLe::ImplyRegressionLe(Space& home, BoolView b, ViewArray<BoolView> & cols, vector<float> *labels, IntView c, int precision):
    RegressionLe ( home, cols, labels, c, precision ), b(b) {
    b.subscribe(home,*this,PC_INT_VAL);
  }

  forceinline
  ImplyRegressionLe::ImplyRegressionLe(Space& home, bool share, ImplyRegressionLe& p)
    : RegressionLe (home, share, p) {
    b.update(home,share,p.b);
  }

  forceinline size_t
  ImplyRegressionLe::dispose(Space& home) {
    assert(!home.failed());
    b.cancel(home,*this,PC_INT_VAL);
    return  RegressionLe::dispose(home);
  }

  Actor*
  ImplyRegressionLe::copy(Space& home, bool share) {
    return new (home) ImplyRegressionLe (home,share,*this);
  }

  ExecStatus
  ImplyRegressionLe::post(Space& home, BoolView b, ViewArray<BoolView> & cols, vector<float> *labels, IntView c, int precision) {

    (void) new (home) ImplyRegressionLe(home,b,cols, labels, c,precision);
    return ES_OK;
  }

  ExecStatus
  ImplyRegressionLe::propagate(Space& home, const ModEventDelta&) {
    if (b.one())
        GECODE_REWRITE(*this,(RegressionLe::post(home,cols,labels,c,precision)));
    if (b.zero())
        return home.ES_SUBSUMED(*this); // couldn't care less

    // maximum of monotone function must be less than or equal to the treshold
    bool reach = propagateRegression ( cols, *labels, c.max () / (float) precision );
    if ( !reach ) {
        GECODE_ME_CHECK(b.zero_none(home));
        return home.ES_SUBSUMED(*this);
    } 
    else 
        if ( cols.assigned () )
            return home.ES_SUBSUMED(*this);
    return ES_FIX;
  }

  /** \brief Post propagator for the regression propagator, reified version
   *
   * Returns Error if not positive unit.
   *
   */
  void imply_regression(Space &home, const BoolVar b, const BoolVarArgs &cols, 
		        vector<float> *labels, IntRelType r, IntVar c, int precision) {
    if (home.failed()) return;

    if (b.one()) {
        return regressionle(home, cols, labels, r, c, precision);
    }
    if (b.zero())
        return; // couldn't care less

    // Only accept IRT_LQ (low error for now)
    if (r != IRT_LQ)
      throw UnknownRelation("ConvexBool::imply_convex");
    
    ViewArray<BoolView> cols0(home,cols);

    GECODE_ES_FAIL((ImplyRegressionLe
                             ::post(home, b, cols0, labels, c, precision)));
  }



}
