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
#include "regression.hh"
#include <stdlib.h>

statRegressionType statRegression;
propagateRegressionType propagateRegression;

InitRegressionHelp *InitRegressionHelp::first = NULL;

// simpe linear search to initialize the regression functions.
// if not found, tries to initialize to the first in the list.
void setRegression ( const char *name ) {
  InitRegressionHelp *loop = InitRegressionHelp::first;
  while ( loop && strcmp ( name, loop->name ) )
    loop = loop->next;
  if ( !loop ) 
    loop = InitRegressionHelp::first;
  if ( loop ) {
    statRegression = loop->statRegression;
    propagateRegression = loop->propagateRegression;
    printf ( "Regression initialized to \"%s\"\n", loop->name );
  }
}

const char *defaultRegression () {
  return InitRegressionHelp::first->name;
}