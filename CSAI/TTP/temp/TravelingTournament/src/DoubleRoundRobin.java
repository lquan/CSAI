import ExamplesJaCoP.Example;
import JaCoP.constraints.Alldiff;
import JaCoP.constraints.XmulCeqZ;
import JaCoP.constraints.XneqC;
import JaCoP.constraints.XneqY;
import JaCoP.core.IntVar;
import JaCoP.core.Store;
import JaCoP.fz.Constraints;
import JaCoP.search.DepthFirstSearch;
import JaCoP.search.IndomainMin;
import JaCoP.search.InputOrderSelect;
import JaCoP.search.Search;
import JaCoP.search.SelectChoicePoint;
import JaCoP.search.SimpleMatrixSelect;
import JaCoP.search.SimpleSelect;
import JaCoP.search.SmallestDomain;
import JaCoP.search.SmallestMax;


public class DoubleRoundRobin {

	private static IntVar[][] elements;
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Store store = new Store();
		int teams = Integer.parseInt(args[0]);
		
		if (teams%2 != 0) {
			System.out.println("input must be even!");
			return;
		}
		int weeks = 2*teams-2;
		elements = new IntVar[teams][weeks];
		
		//creating variables 
		for (int i =0; i < teams; i++) {
			for (int j=0; j< weeks; j++) {
				elements[i][j] = new IntVar(store,"team " + i+1 + " in week "+ j+1, -teams, teams);
			}
		}
		
		//row constraint
		for (int i=0; i< teams; i++) {
			//permutations
			store.impose(new Alldiff(elements[i]));
	
			for (int j=0;j<teams;j++) {
				 //team cannot play against itself
				store.impose(new XneqC(elements[i][j],0));
				store.impose(new XneqC(elements[i][j],i+1));
				store.impose(new XneqC(elements[i][j],-(i+1)));
				
				store.impose(new XmulCeqZ(elements[i][j], -1, elements[j][i]));
			}
			
			
		}
		
		//column constraint
		for (int j=0; j< weeks; j++) {
			IntVar[] column = new IntVar[teams];
			for (int i=0; i< teams; i++) {
				column[i] = elements[i][j];
			}
			store.impose(new Alldiff(column));
		}
		
		
		
		
		//store.print();
		
		// search for a solution and print results 
        Search<IntVar> search = new DepthFirstSearch<IntVar>(); 
        SelectChoicePoint<IntVar> select = 
            new SimpleMatrixSelect<IntVar>(elements, new SmallestMax<IntVar>(), new IndomainMin<IntVar>()); 
        search.getSolutionListener().searchAll(true); 
        // record solutions; if not set false 
        search.getSolutionListener().recordSolutions(true); 
        boolean result = search.labeling(store, select);
        //search.printAllSolutions();
        
      //print the result
		Example.printMatrix(elements,teams,weeks);

	}

}
