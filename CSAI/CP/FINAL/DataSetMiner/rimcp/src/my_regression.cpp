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
#include "common/regression.hh"
#include <stdlib.h>
#include <iostream>

/// YOU NEED TO MODIFY THIS FILE IN ORDER TO IMPLEMENT A NEW REGRESSION 

Ritemset_Stat statMyRegression ( const BoolVarArray &transactions, const vector<float> &labels ) {
  
  /// THIS FUNCTION NEEDS TO COMPUTE STATISTICS FOR AN ITEMSET BASED ON THE TRANSACTIONS
  /// IT COVERS. 
  Ritemset_Stat stat;
  
  // calculate the number and average labels of the (un)covered
  double average_label_covered = 0; 	//average of labels of contained example: m1
  int nb_covered = 0; 			//number of contained examples
  double average_label_uncovered = 0; 	//average of labels of not contained examples: m2
  int nb_uncovered = 0;			//number of not contained examples
  
  /// EXAMPLE OF LOOP THROUGH TRANSACTIONS
  for ( int i = 0; i < transactions.size (); ++i ) {
    if ( transactions[i].one () ) {
		/// DO SOMETHING BASED ON labels[i];
		average_label_covered += labels[i];       
		nb_covered++;   
    }
    else {
        /// transactions[i].zero ()
        /// DO SOMETHING ELSE BASED ON labels[i];
		average_label_uncovered += labels[i];
		nb_uncovered++;
    }
  }
  //calculate the averages
	if( nb_covered != 0) {
		average_label_covered /= nb_covered;
	}

	if (nb_uncovered !=0) {
		 average_label_uncovered /= nb_uncovered;
	}
  
  

  // now calculate the distances for the mean square error calculation
  double error = 0;
  double diff = 0; //temp variable indiciating the difference between m1 or m2 and the example
  for ( int i = 0; i < transactions.size (); ++i ) {
    if ( transactions[i].one () ) {
		diff = (labels[i]-average_label_covered);

    }
    else {
        diff = (labels[i]-average_label_uncovered); //error also takes in account uncovered???
    }
    error += (diff * diff);
  }
  
  /// ASSIGN stat.prediction - the prediction made for this itemset based on the transactions it covers (for instance, the mean of the covered transactions)
  /// ASSIGN stat.tot - the number of transactions covered by this itemset
  /// ASSIGN stat.value - the error measure calculated for this itemset
  
  stat.tot = nb_covered;
  stat.value = error;
  stat.prediction = average_label_covered;

  return stat;
}

bool propagateMyRegression ( const ViewArray<BoolView> &transactions, const vector<float> &labels, float score ) {
  
  /// THIS FUNCTION NEEDS TO COMPUTE WHETHER, BASED ON THE CURRENT ASSIGNMENTS TO TRANSACTIONS
  /// VARIABLES, THE DESIRED 'SCORE' CAN STILL BE REACHED  

  /// ** IT CAN BE ASSUMED THAT THE TRANSACTIONS ARE SORTED IN ORDER OF THEIR LABEL, SMALLEST LABELS FIRST **
  
  // calculate the number and average labels of the (un)covered
  double average_label_covered = 0; 	//average of labels of contained example: m1
  int nb_covered = 0; 			//number of contained examples
  double average_label_uncovered = 0; 	//average of labels of not contained examples: m2
  int nb_uncovered = 0;			//number of not contained examples

  for (int i = 0; i < transactions.size(); ++i) {
	if ( transactions[i].assigned () )  {
	  /// assigned () MEANS THAT WE KNOW WHETHER THE TRANSACTION IS ZERO OR ONE
	  if ( transactions[i].one () ) {
			/// COMPUTE SOMETHING
			average_label_covered += labels[i];
			nb_covered++;
      }
      else {
		  	average_label_uncovered += labels[i];
			nb_uncovered++;
      }
	}

    else {
      /// IN THIS CASE BOTH ZERO AND ONE ARE POSSIBLE.
      /// ESSENTIALLY, WE NEED TO DETERMINE WHAT IS THE LOWEST ERROR THAT CAN STILL BE REACHED
      /// WHEN WE DON'T KNOW THE VALUE OF THIS TRANSACTION YET.
      //max_reach_support++;
    }
  }

  //calculate the averages
	if( nb_covered != 0) {
		average_label_covered /= nb_covered;
	}
	if (nb_uncovered !=0) {
		 average_label_uncovered /= nb_uncovered;
	}

  // now calculate the distances for the mean square error calculation
  double error = 0;
  double diff = 0; //temp variable indiciating the difference between m1 or m2 and the example
  //bool all_unassigned = true;
  for ( int i = 0; i < transactions.size (); ++i ) {
	if (transactions[i].assigned()) {
		//all_unassigned = false;
		if ( transactions[i].one () ) {
			diff = (labels[i]-average_label_covered);
    	}
    	else {
    	    diff = (labels[i]-average_label_uncovered);
		}
    	error += (diff * diff);
    	
	}
}
	

	/***Een aanvullende voorwaarde zou kunnen zijn dat de itemset een zeker minimaal aantal voorbeelden bedekt.**/
	return error <= score; //&& nb_covered > 0;

}

/// THE FOLLOWING STATEMENT ENSURES THAT THE ABOVE TWO FUNCTIONS ARE KNOWN TO RIMCP
/// "my" IS THE NAME BY WHICH THEY CAN BE SPECIFIED ON THE COMMAND LINE
registerRegression ( "my", statMyRegression, propagateMyRegression );

/// IT IS POSSIBLE TO IMPLEMENT MULTIPLE REGRESSION FUNCTIONS AND BOUNDS FOR THESE FUNCTIONS.
/// IN THIS CASE, DEFINE FURTHER statRegression and propagateRegression FUNCIONS;
/// ADD A registerRegression STATEMENT TO MAKE THEM KNOWN.
