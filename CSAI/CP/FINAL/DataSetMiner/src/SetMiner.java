import weka.core.converters.ConverterUtils.DataSource;
import weka.core.converters.ArffSaver;
import weka.core.Instance;
import weka.core.Instances;
import java.io.*;
import java.util.*;

/**
 * Capita Selecta AI - Regel-gebaseerde Regressie
 * http://people.cs.kuleuven.be/~siegfried.nijssen/capita2011/opgave.html
 * @author Philippe Tanghe & Li Quan
 * @date 6/04/11
 */
class SetMiner {
	
	// the parameters
	private static final boolean PRUNE = true;    
	private static final double RULECOST = 5;
	private static final int MAX_NB_LEAF = 3;               
	private static final boolean PREDICT_AVERAGE = false; //for average set true
	
	
	/**
 	* een eerste arff bestandsnaam, verwijzend naar het bestand met trainingsvoorbeelden (invoer)
    * 
    * een tweede arff bestandsnaam, verwijzend naar het bestand met testvoorbeelden; hierop moet je algoritme voorspellingen gaan doen (invoer)
    * 
    * een derde arff bestandsnaam, verwijzend naar het bestand waarin voor elk testvoorbeeld in de laatste kolom opgeslagen wordt wat de voorspelling is 
    * (voorbeelden in deze arff moeten dezelfde volgorde hebben als in de arff met testvoorbeelden) (uitvoer)
    *
    * een vierde arff bestandsnaam, waarin de gevonden itemsets worden opgeslagen. 
   	* In dit bestand moet elke rij één gevonden itemset bevatten. 
    * De itemset moet voorgesteld worden door een 1 te plaatsen in de kolommen overeenkomstig met de gevonden items. (uitvoer)
	*/
	public static void main(String[] args) {
		if (args.length < 4) {
			throw new IllegalArgumentException("usage: 4 parameters!!!");
		}
		try {
			// Read the data specified in the command line
			DataSource source = new DataSource(args[0]);
			Instances trainingDataSet = source.getDataSet();
			if (trainingDataSet.classIndex() == -1)
				trainingDataSet.setClassIndex(trainingDataSet.numAttributes() - 1);
			
			/*//normalization
			double scale = getPrediction(data,true);
			data = normalize(data, scale);
			*/
			
			Instances predictionsOnTrainingSet = new Instances(trainingDataSet); 	// copy the dataset to make predictions for
			Instances itemsets = new Instances(trainingDataSet,0); 			// only headers for itemsets (args[3])
			
			DataSource source2 = new DataSource(args[1]);
			Instances predictionsOnTestSet = source2.getDataSet();           //the predictions of args[1] into args[2]
			if (predictionsOnTestSet.classIndex() == -1)
				predictionsOnTestSet.setClassIndex(predictionsOnTestSet.numAttributes() - 1);
			
			
			// The recursive iterative rule searching
			buildRegressionModel(trainingDataSet, itemsets, new int[0]);
			applyRules(itemsets, predictionsOnTrainingSet);
			
			/*//denormalization
			data = normalize(data,1.0/scale);
			predictionsoriginal = normalize(predictionsoriginal,1.0/scale);
			itemsets = normalize(itemsets,1.0/scale);
			*/
			
			/*double error = calcError(trainingDataSet,predictionsOnTrainingSet);
			System.out.println("error on training set before pruning: " + error);
			System.out.println("number of rules after pruning " + itemsets.numInstances());
			// do the predictions for the given instances
			Instances testOriginal = new Instances(predictionsOnTestSet);*/
			
			applyRules(itemsets, predictionsOnTestSet);
			
			/*
			error = calcError(testOriginal, predictionsOnTestSet);
			System.out.println("the error on the test set before pruning is: " + error);
			*/
			
			// Prune the rule set
			if (PRUNE) {
				itemsets = pruneRules(trainingDataSet, predictionsOnTrainingSet, itemsets);
			}
			
			// do the predictions for the test 
			applyRules(itemsets, predictionsOnTrainingSet);
			
			/*
			error = calcError(trainingDataSet, predictionsOnTrainingSet);
			System.out.println("the error on the training set after pruning is: " + error);
			System.out.println("number of rules after pruning " + itemsets.numInstances());
			*/
			
			
			// do the predictions for the given instances
			applyRules(itemsets, predictionsOnTestSet);
			
			/*
			error = calcError(testOriginal, predictionsOnTestSet);
			System.out.println("the error on the test set after pruning is: " + error);
			*/
					
			// Write the data to a arff file: the two output arff files 
			writeData(predictionsOnTestSet, args[2]);
			writeData(itemsets, args[3]);
			// + 1 for the original training examples
			// writeData(predictionsOnTrainingSet, "predictionsoriginal.arff");

		}
		catch ( Exception e ) {
			e.printStackTrace();
		}
	}

	/**
	 * Applies the rules in itemsets on the dataset in predictions
	 * @param itemsets
	 * @param predictions
	 */
	private static void applyRules(Instances itemsets, Instances predictions) {
		for (int i=0; i<predictions.numInstances(); ++i) {
			Instance instance = predictions.instance(i);
			boolean covered = true;
			for (int j= 0; j<itemsets.numInstances(); ++j) {
				Instance rule = itemsets.instance(j);
				covered = true;
				for (int k=0; k< itemsets.numAttributes() -1 ; ++k) {
					if (rule.value(k)==1) {
						covered = instance.value(k)==1;
						if(!covered){
							break;
						}
					}
					
				}
				if (covered) {
					
					instance.setClassValue(rule.classValue());
					break;
				}
			}
		}
	}


	/**
	 * Calculates L1 distance error between the actual and predicted labels
	 */
	private static double calcError(Instances data, Instances data2) {
		// calculate the total l1 norm of the class values of the two data sets 
		double error = 0;
		for (int i=0; i < data.numInstances(); ++i) {
			error += Math.abs(data.instance(i).classValue() - data2.instance(i).classValue());			
		}
		return error;
	}

	/**
	 * Writes the data to output file.
	 */
	private static void writeData(Instances data, String filename) {
		try {
			ArffSaver saver = new ArffSaver();
			saver.setInstances(data);
			saver.setFile(new File(filename));
			saver.writeBatch();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * Prune rules
	 * @param data		original training data (with original labels)
	 * @param predOr	training data with predicted labels
	 * @param itemsets	item sets to be used as rules
	 */
	private static Instances pruneRules(Instances data, Instances predOr, Instances itemsets){
		int originalSize;
		int newSize;
		Instances newPredOr = new Instances(predOr);
		do	{
			originalSize = itemsets.numInstances();
			itemsets = pruneRule(data, newPredOr, itemsets);
			newSize = itemsets.numInstances();
			applyRules(itemsets,newPredOr);
			}
			while(newSize < originalSize);
		return itemsets;
	}
	
	/**
	 * Prune one rule that leads to the least increasing error.
	 */
	private static Instances pruneRule(Instances data, Instances predOr, Instances itemsets) {
		Instances bestCopy = itemsets;
		Instances workingData = new Instances(predOr);
		double bestError = calcError(data, predOr);
		for(int i = itemsets.numInstances() - 2; i > 0 ; i--){
			Instances itemsetCopy = new Instances(itemsets);
			itemsetCopy.delete(i);
			applyRules(itemsetCopy, workingData);
			double error = calcError(data, workingData);
			if( calcNewError(error) < bestError ){ 
				bestError = calcNewError(error);
				bestCopy = itemsetCopy;
			}
		}
		return bestCopy;
	}
	
	private static double calcNewError(double error) {
		return error - RULECOST;
	}
	

	/**
	 * Builds the regression tree and infer the rules.
	 */
	private static void buildRegressionModel(Instances data, Instances itemsets, int[] items) throws Exception {
		if (data.numInstances() <= MAX_NB_LEAF) { //stop criterion possible needs to refined: data.variance(data.numAttributes()-1) < 10)
			double prediction =  getPrediction(data,PREDICT_AVERAGE); 
			double[] attributes = new double[data.numAttributes()];
			for (int i : items) {
				attributes[i] = 1;
			}
			attributes[attributes.length-1] = prediction;
			itemsets.add(new Instance(1, attributes ));
		}
		else{
			int[] items2 = findPattern(data);
			InstanceSelection data2 = select(data, items2);
			items2 = union(items2, items);

			// depth-first creation of the tree
			if (data2.getSelected().numInstances() != 0) {
				buildRegressionModel(data2.getSelected(), itemsets, items2);			
			}
			
			if (data2.getNotSelected().numInstances() != 0) {
				buildRegressionModel(data2.getNotSelected(), itemsets, items);
			}
			
			
		}
		
	}


	/**
	 * Union of the two itemsets
	 */
	private static int[] union(int[] items1, int[] items2) {
		Set<Integer> itemSet = new HashSet<Integer>();
		for(int i : items1) {
			itemSet.add(i);
		}
		for(int i : items2){
			itemSet.add(i);
		}
		int[] items = new int[itemSet.size()];
		int i = 0;
		for(int val : itemSet){
			items[i++] = val; 
		}
		return items;
	}

	//================================================== median
	//  Precondition: Array must be sorted
	private static double median(double[] m) {
		int middle = m.length/2;  // subscript of middle element
		if (m.length%2 == 1) {
			// Odd number of elements -- return the middle one.
			return m[middle];
		} else {
			// Even number -- return average of middle two
			// Must cast the numbers to double before dividing.
			return (m[middle-1] + m[middle]) / 2.0;
		}
	}//end method median


	/**
	 * Returns the prediction, either average or median
	 */
	private static double getPrediction(Instances selected, boolean average) {
		if (average)
			return selected.meanOrMode(selected.numAttributes() - 1);
		else {
			double[] values = selected.attributeToDoubleArray(selected.numAttributes() - 1);
			Arrays.sort(values);
			return median(values);
		}
	}

	/***
	 * Apply the constraint programming system to find the 'best' pattern in a dataset
	 * @param data
	 * @return int[] best pattern in the given dataset
	 * @throws Exception
	 */
	public static int[] findPattern ( Instances data ) throws Exception {
		// Write the data to a arff file
		ArffSaver saver = new ArffSaver();
		saver.setInstances(data);
		saver.setFile(new File("tmpdata.arff"));
		saver.writeBatch();

		// Run the CP system on the dataset - update the command line to the appropriate path
		Runtime rt = Runtime.getRuntime();

		// change command AND/OR environment path 
		String[] command = {"rimcp/src/rimcp", "-datafile", "tmpdata.arff", "-solfile", "tmppattern"};
		String[] envpath = {"LD_LIBRARY_PATH=rimcp/lib/gecode-3.4.2/"};

		Process pr = rt.exec(command,envpath);
		System.out.println("Running rimcp on " + data.numInstances () + " instances" );

		int exitVal = pr.waitFor();
		System.out.println("Exited with error code "+exitVal);

		// Read the pattern file written by the CP system
		BufferedReader in = new BufferedReader(new FileReader("tmppattern"));
		String line, lastline = "";
		if (!in.ready())
			throw new IOException();
		while ((line = in.readLine()) != null) {
			lastline = line;
		}
		System.out.println("Pattern found: " + lastline );

		// Parse the last line (containing the 'best' pattern) into an array of items
		String items[] = lastline.split(" ");
		int items2 [] = new int[items.length-2];

		for ( int i = 0; i <items.length-2; i++ ) {
			items2[i] = Integer.parseInt(items[i]);
			System.out.println(data.attribute ( items2[i] ).name ());
		}
		in.close();

		System.out.println();
		// Return the set of items
		return items2;
	}
	
	/**
	 * Selects instances according to the itemset
	 * @see InstanceSelection
	 */
	public static InstanceSelection select ( Instances data, int items[] ) {
		/*Instances data2 = new Instances ( data, 0 );
		Instances data3 = new Instances(data,0);
		Instances[] result = {data3, data2};*/
		InstanceSelection result = new InstanceSelection(data);
		
		boolean isCovered = false;
		
		for ( int i = 0; i < data.numInstances (); ++i ) {
			isCovered = false;
			for ( int j = 0; j < items.length; ++j ) {
				if ( data.instance ( i ).value ( items[j] ) == 0 ) {
					isCovered = false;
					// one item is missing, add immediately
					//result.add ( data.instance ( i ) );
					result.addNotSelected(data.instance(i));
					result.addIndicesNotSelected(i);
					break;
				}
				
				else {
					isCovered = true;
				}
			}
			
			if (isCovered) {
				//data3.add(data.instance(i));
				result.addSelected(data.instance(i));
				result.addIndicesSelected(i);
			}
		}
		
		return result;
	}
	

	private static Instances normalize(Instances in, double factor) {
		Instances out = new Instances(in);
		
		Instance instance;
		for (int i=0; i < out.numInstances(); ++i) {
			instance = out.instance(i);
			instance.setClassValue(instance.classValue()/factor);		
		}
		return out;
		
		
	}
	
	private static double findMax(Instances in) {
		double[] values = new double[in.numInstances()];
		
		for (int i =0; i < in.numInstances(); ++i) {
			values[i] = in.instance(i).classValue();
		}
		
		Arrays.sort(values);
		
		return values[values.length-1];
		
		
	}
	
}
