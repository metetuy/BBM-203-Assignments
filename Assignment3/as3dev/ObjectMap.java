

import java.util.HashMap;
import java.util.Map;

public class ObjectMap {
	private Map<String, Object> materialMap;

	public ObjectMap() {
		materialMap = new HashMap<>();
	}

	public void addDrillMachine(int row, int col, DrillMachine drillMachine) {
		String key = generateKey(row, col);
		materialMap.put(key, drillMachine);
	}

	public String getClassType(int row, int col) {
		String key = generateKey(row, col);
		Object obj = materialMap.get(key);
		if (obj instanceof DrillMachine) {
			return "drillMachine";
		} else if (obj instanceof Material) {
			return "material";
		}
		return null;
	}

	// Add material to the map at specific coordinates
	public void addMaterial(int row, int col, Material material) {
		String key = generateKey(row, col);
		materialMap.put(key, material);
	}

	// Get material from the map at specific coordinates
	public Material getMaterial(int row, int col) {
		String key = generateKey(row, col);
		return (Material) materialMap.get(key);
	}

	public DrillMachine getDrillMachine(int row, int col) {
		String key = generateKey(row, col);
		return (DrillMachine) materialMap.get(key);
	}

	public void removeDrillMachine(int row, int col) {
		String key = generateKey(row, col);
		materialMap.remove(key);
		Material empty = new Material("empty", true, 0, 0);
		materialMap.put(key, empty);
	}

	// Remove material from the map at specific coordinates
	public void removeMaterial(int row, int col) {
		String key = generateKey(row, col);
		materialMap.remove(key);
		Material empty = new Material("empty", true, 0, 0);
		materialMap.put(key, empty);
	}

	// Generate a unique key based on row and column coordinates
	private String generateKey(int row, int col) {
		return row + "," + col;
	}

	// Generate a string representation of the map
	public String mapToString() {
		StringBuilder builder = new StringBuilder();
		for (int row = 0; row < 16; row++) {
			for (int col = 0; col < 14; col++) {
				Object obj = materialMap.get(generateKey(row, col));
				if (obj instanceof DrillMachine) {
					builder.append("DrillMachine ");
				} else if (obj instanceof Material) {
					builder.append(((Material) obj).getMaterialType()).append(" ");
				} else {
					builder.append("Empty ");
				}
			}
			builder.append("\n");
		}
		return builder.toString();
	}
}
