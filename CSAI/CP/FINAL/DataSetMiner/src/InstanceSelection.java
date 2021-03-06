import java.util.ArrayList;
import java.util.List;

import weka.core.Instance;
import weka.core.Instances;

/**
 * Represents the instance that cover and do not cover the itemset
 * @author Philippe Tanghe & Li Quan
 * @date 6/04/11
 */
public class InstanceSelection {

	
	private Instances selected;
	private List<Integer> indicesSelected;
	private List<Integer> indicesNotSelected;
	
	private Instances notSelected;
	
	public InstanceSelection(Instances data) {	
		selected = new Instances(data,0);
		notSelected = new Instances(data,0);
		indicesSelected = new ArrayList<Integer>();
		indicesNotSelected = new ArrayList<Integer>();
	}

	public void addSelected(Instance instance) {
		this.selected.add(instance);
	}

	public Instances getSelected() {
		return selected;
	}
	
	public boolean noneSelected() {
		return this.selected.numInstances() == 0;
	}

	public void addNotSelected(Instance instance) {
		this.notSelected.add(instance);
	}

	public Instances getNotSelected() {
		return notSelected;
	}

	public void addIndicesSelected(int i) {
		this.indicesSelected.add(i);
	}

	public List<Integer> getIndicesSelected() {
		return indicesSelected;
	}
	
	public void addIndicesNotSelected(int i) {
		this.indicesNotSelected.add(i);
	}
	
	public List<Integer> getIndicesNotSelected() {
		return indicesNotSelected;
	}
	
}
