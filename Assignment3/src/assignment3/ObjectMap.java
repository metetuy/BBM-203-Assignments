package assignment3;

import java.util.HashMap;
import java.util.Map;

/**
 * Represents the object map in the game.
 */
public class ObjectMap {
	private Map<String, Object> materialMap;

	/**
	 * Constructs an ObjectMap.
	 */
	public ObjectMap() {
		materialMap = new HashMap<>();
	}

	/**
	 * Adds a drill machine to the map at specific coordinates.
	 * 
	 * @param row          The row coordinate.
	 * @param col          The column coordinate.
	 * @param drillMachine The drill machine to add.
	 */
	public void addDrillMachine(int row, int col, DrillMachine drillMachine) {
		String key = generateKey(row, col);
		materialMap.put(key, drillMachine);
	}

	/**
	 * Gets the class type at specific coordinates.
	 * 
	 * @param row The row coordinate.
	 * @param col The column coordinate.
	 * @return The class type at the specified coordinates.
	 */
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

	/**
	 * Adds material to the map at specific coordinates.
	 * 
	 * @param row      The row coordinate.
	 * @param col      The column coordinate.
	 * @param material The material to add.
	 */
	public void addMaterial(int row, int col, Material material) {
		String key = generateKey(row, col);
		materialMap.put(key, material);
	}

	/**
	 * Gets the material from the map at specific coordinates.
	 * 
	 * @param row The row coordinate.
	 * @param col The column coordinate.
	 * @return The material at the specified coordinates.
	 */
	public Material getMaterial(int row, int col) {
		String key = generateKey(row, col);
		return (Material) materialMap.get(key);
	}

	/**
	 * Gets the drill machine from the map at specific coordinates.
	 * 
	 * @param row The row coordinate.
	 * @param col The column coordinate.
	 * @return The drill machine at the specified coordinates.
	 */
	public DrillMachine getDrillMachine(int row, int col) {
		String key = generateKey(row, col);
		return (DrillMachine) materialMap.get(key);
	}

	/**
	 * Removes the drill machine from the map at specific coordinates.
	 * 
	 * @param row The row coordinate.
	 * @param col The column coordinate.
	 */
	public void removeDrillMachine(int row, int col) {
		String key = generateKey(row, col);
		materialMap.remove(key);
		Material empty = new Material("empty", true, 0, 0);
		materialMap.put(key, empty);
	}

	/**
	 * Removes material from the map at specific coordinates.
	 * 
	 * @param row The row coordinate.
	 * @param col The column coordinate.
	 */
	public void removeMaterial(int row, int col) {
		String key = generateKey(row, col);
		materialMap.remove(key);
		Material empty = new Material("empty", true, 0, 0);
		materialMap.put(key, empty);
	}

	/**
	 * Generates a unique key based on row and column coordinates.
	 * 
	 * @param row The row coordinate.
	 * @param col The column coordinate.
	 * @return The generated key.
	 */
	private String generateKey(int row, int col) {
		return row + "," + col;
	}

	/**
	 * Generates a string representation of the map.
	 * 
	 * @return The string representation of the map.
	 */
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