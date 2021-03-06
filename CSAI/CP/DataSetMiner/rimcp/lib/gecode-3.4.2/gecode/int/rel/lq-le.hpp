/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *     Gabor Szokoli <szokoli@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2003
 *     Gabor Szokoli, 2003
 *
 *  Last modified:
 *     $Date: 2010-03-03 17:32:21 +0100 (Wed, 03 Mar 2010) $ by $Author: schulte $
 *     $Revision: 10364 $
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

namespace Gecode { namespace Int { namespace Rel {

  /*
   * Less or equal propagator
   *
   */

  template<class View>
  forceinline
  Lq<View>::Lq(Home home, View x0, View x1)
    : BinaryPropagator<View,PC_INT_BND>(home,x0,x1) {}

  template<class View>
  ExecStatus
  Lq<View>::post(Home home, View x0, View x1) {
    GECODE_ME_CHECK(x0.lq(home,x1.max()));
    GECODE_ME_CHECK(x1.gq(home,x0.min()));
    if (!same(x0,x1) && (x0.max() > x1.min()))
      (void) new (home) Lq<View>(home,x0,x1);
    return ES_OK;
  }

  template<class View>
  forceinline
  Lq<View>::Lq(Space& home, bool share, Lq<View>& p)
    : BinaryPropagator<View,PC_INT_BND>(home,share,p) {}

  template<class View>
  Actor*
  Lq<View>::copy(Space& home, bool share) {
    return new (home) Lq<View>(home,share,*this);
  }

  template<class View>
  ExecStatus
  Lq<View>::propagate(Space& home, const ModEventDelta&) {
    GECODE_ME_CHECK(x0.lq(home,x1.max()));
    GECODE_ME_CHECK(x1.gq(home,x0.min()));
    return (x0.max() <= x1.min()) ? home.ES_SUBSUMED(*this) : ES_FIX;
  }




  /*
   * Less propagator
   *
   */
  template<class View>
  forceinline
  Le<View>::Le(Home home, View x0, View x1)
    : BinaryPropagator<View,PC_INT_BND>(home,x0,x1) {}

  template<class View>
  ExecStatus
  Le<View>::post(Home home, View x0, View x1) {
    if (same(x0,x1))
      return ES_FAILED;
    GECODE_ME_CHECK(x0.le(home,x1.max()));
    GECODE_ME_CHECK(x1.gr(home,x0.min()));
    if (x0.max() >= x1.min())
      (void) new (home) Le<View>(home,x0,x1);
    return ES_OK;
  }

  template<class View>
  forceinline
  Le<View>::Le(Space& home, bool share, Le<View>& p)
    : BinaryPropagator<View,PC_INT_BND>(home,share,p) {}

  template<class View>
  Actor*
  Le<View>::copy(Space& home, bool share) {
    return new (home) Le<View>(home,share,*this);
  }

  template<class View>
  ExecStatus
  Le<View>::propagate(Space& home, const ModEventDelta&) {
    GECODE_ME_CHECK(x0.le(home,x1.max()));
    GECODE_ME_CHECK(x1.gr(home,x0.min()));
    return (x0.max() < x1.min()) ? home.ES_SUBSUMED(*this) : ES_FIX;
  }



  /*
   * Reified less or equal propagator
   *
   */

  template<class View, class CtrlView>
  forceinline
  ReLq<View,CtrlView>::ReLq(Home home, View x0, View x1, CtrlView b)
    : ReBinaryPropagator<View,PC_INT_BND,CtrlView>(home,x0,x1,b) {}

  template<class View, class CtrlView>
  ExecStatus
  ReLq<View,CtrlView>::post(Home home, View x0, View x1, CtrlView b) {
    if (b.one())
      return Lq<View>::post(home,x0,x1);
    if (b.zero())
      return Le<View>::post(home,x1,x0);
    if (!same(x0,x1)) {
      switch (rtest_lq(x0,x1)) {
      case RT_TRUE:
        GECODE_ME_CHECK(b.one_none(home)); break;
      case RT_FALSE:
        GECODE_ME_CHECK(b.zero_none(home)); break;
      case RT_MAYBE:
        (void) new (home) ReLq<View,CtrlView>(home,x0,x1,b); break;
      default: GECODE_NEVER;
      }
    } else {
      GECODE_ME_CHECK(b.one_none(home));
    }
    return ES_OK;
  }

  template<class View, class CtrlView>
  forceinline
  ReLq<View,CtrlView>::ReLq(Space& home, bool share, ReLq& p)
    : ReBinaryPropagator<View,PC_INT_BND,CtrlView>(home,share,p) {}

  template<class View, class CtrlView>
  Actor*
  ReLq<View,CtrlView>::copy(Space& home, bool share) {
    return new (home) ReLq<View,CtrlView>(home,share,*this);
  }

  template<class View, class CtrlView>
  ExecStatus
  ReLq<View,CtrlView>::propagate(Space& home, const ModEventDelta&) {
    if (b.one())
      GECODE_REWRITE(*this,Lq<View>::post(home(*this),x0,x1));
    if (b.zero())
      GECODE_REWRITE(*this,Le<View>::post(home(*this),x1,x0));
    switch (rtest_lq(x0,x1)) {
    case RT_TRUE:
      GECODE_ME_CHECK(b.one_none(home));  return home.ES_SUBSUMED(*this);
    case RT_FALSE:
      GECODE_ME_CHECK(b.zero_none(home)); return home.ES_SUBSUMED(*this);
    case RT_MAYBE:
      break;
    default: GECODE_NEVER;
    }
    return ES_FIX;
  }

  /*
   * Reified less or equal propagator involving one variable
   *
   */

  template<class View, class CtrlView>
  forceinline
  ReLqInt<View,CtrlView>::ReLqInt(Home home, View x, int c0, CtrlView b)
    : ReUnaryPropagator<View,PC_INT_BND,CtrlView>(home,x,b), c(c0) {}

  template<class View, class CtrlView>
  ExecStatus
  ReLqInt<View,CtrlView>::post(Home home, View x, int c, CtrlView b) {
    if (b.one()) {
      GECODE_ME_CHECK(x.lq(home,c));
    } else if (b.zero()) {
      GECODE_ME_CHECK(x.gr(home,c));
    } else {
      switch (rtest_lq(x,c)) {
      case RT_TRUE:
        GECODE_ME_CHECK(b.one_none(home)); break;
      case RT_FALSE:
        GECODE_ME_CHECK(b.zero_none(home)); break;
      case RT_MAYBE:
        (void) new (home) ReLqInt<View,CtrlView>(home,x,c,b); break;
      default: GECODE_NEVER;
      }
    }
    return ES_OK;
  }


  template<class View, class CtrlView>
  forceinline
  ReLqInt<View,CtrlView>::ReLqInt(Space& home, bool share, ReLqInt& p)
    : ReUnaryPropagator<View,PC_INT_BND,CtrlView>(home,share,p), c(p.c) {}

  template<class View, class CtrlView>
  Actor*
  ReLqInt<View,CtrlView>::copy(Space& home, bool share) {
    return new (home) ReLqInt<View,CtrlView>(home,share,*this);
  }

  template<class View, class CtrlView>
  ExecStatus
  ReLqInt<View,CtrlView>::propagate(Space& home, const ModEventDelta&) {
    if (b.one()) {
      GECODE_ME_CHECK(x0.lq(home,c)); goto subsumed;
    }
    if (b.zero()) {
      GECODE_ME_CHECK(x0.gr(home,c)); goto subsumed;
    }
    switch (rtest_lq(x0,c)) {
    case RT_TRUE:
      GECODE_ME_CHECK(b.one_none(home)); goto subsumed;
    case RT_FALSE:
      GECODE_ME_CHECK(b.zero_none(home)); goto subsumed;
    case RT_MAYBE:
      break;
    default: GECODE_NEVER;
    }
    return ES_FIX;
  subsumed:
    return home.ES_SUBSUMED(*this);
  }

}}}

// STATISTICS: int-prop

