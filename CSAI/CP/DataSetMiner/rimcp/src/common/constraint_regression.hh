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

#include <gecode/kernel.hh>
#include <gecode/int.hh>
#include <gecode/iter.hh>
#include <gecode/int/rel.hh>
#include <vector>
#include "regression.hh"


namespace Constraint_Regression {
  using namespace ::Gecode;
  using namespace ::Gecode::Int;
  using namespace std;

  /**
   * \brief Base-class for monotone function boolean propagators
   *
   * This class NEEDS a global function:
   * monotone_function(int pos_total, int pos, int neg_total, int neg, int precision)
   */
  class RegressionLe : public Propagator {
  protected:

    ViewArray<BoolView> cols;
    IntView c;
    /// Precision of treshold-integer conversion (eg. 1000)
    int precision;
    /// Pointer to vector of labels - note that labels are allocated once and never deallocated properly in this code
    vector<float> *labels; 

    /// Constructor for creation
    RegressionLe(Space& home, ViewArray<BoolView> &cols, vector<float> *labels, IntView c, int precision);
    /// Constructor for cloning \a p
    RegressionLe(Space& home, bool share, RegressionLe& p);
  public:
    /// Cost function (defined as low linear)
    virtual PropCost cost(const Space& home, const ModEventDelta& med) const;
    /// Delete propagator and return its size
    virtual size_t dispose(Space& home);
    /// Create copy during cloning
    virtual Actor* copy(Space& home, bool share);
    /// Perform propagation
    virtual ExecStatus propagate(Space& home, const ModEventDelta& med);
    /// Post propagator but
    static ExecStatus post(Space& home, ViewArray<BoolView> &cols, vector<float> *labels, IntView c, int precision);
  };

  void regressionle(Space& home, const BoolVarArgs &cols, vector<float> *labels,
                    IntRelType r, IntVar c, int precision);

  /************************************
   *      REIFY-IMPLIED               *
   ***********************************/

  /**
   * \brief Base-class for reify-implied monotone function boolean propagators
   *
   */
  class ImplyRegressionLe : public RegressionLe {
  protected:
    /// reify-implication variable
    BoolView b;

    ImplyRegressionLe(Space& home, BoolView b, ViewArray<BoolView> & cols, vector<float> *labels, IntView c, int precision);
    /// Constructor for cloning \a p
    ImplyRegressionLe(Space& home, bool share, ImplyRegressionLe & p);
  public:
    /// Delete propagator and return its size
    virtual size_t dispose(Space& home);
    /// Create copy during cloning
    virtual Actor* copy(Space& home, bool share);
    /// Perform propagation
    virtual ExecStatus propagate(Space& home, const ModEventDelta& med);
    /// Post propagator
    static ExecStatus post(Space& home, BoolView b, ViewArray<BoolView> & cols, vector<float> *labels, IntView c, int precision);
  };

  void imply_regression(Space &home, const BoolVar b, const BoolVarArgs &cols, 
		        vector<float> *labels, IntRelType r, IntVar c, int precision);

}
