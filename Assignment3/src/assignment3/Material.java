package assignment3;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;

import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

/**
 * Represents a material in the game.
 */
public class Material {
	private String materialType;
	private boolean isMinable;
	private int value;
	private int weight;

	// Array containing the types of materials
	private static final String[] MATERIAL_TYPES = { "ironium", "bronzium", "diamond", "emerald", "platinum",
			"goldium" };

	// Map to store material information
	public static final Map<String, List<Integer>> MATERIAL_MAP = new HashMap<>();
	static {
		// Add material information to the map
		MATERIAL_MAP.put("ironium", createMaterialInfo(30, 10));
		MATERIAL_MAP.put("bronzium", createMaterialInfo(60, 10));
		MATERIAL_MAP.put("goldium", createMaterialInfo(250, 20));
		MATERIAL_MAP.put("platinum", createMaterialInfo(750, 30));
		MATERIAL_MAP.put("emerald", createMaterialInfo(5000, 60));
		MATERIAL_MAP.put("diamond", createMaterialInfo(100000, 100));
	}

	/**
	 * Constructs a material with the specified attributes.
	 * 
	 * @param materialType The type of material.
	 * @param isMinable    Indicates if the material is minable.
	 * @param value        The value of the material.
	 * @param weight       The weight of the material.
	 */
	public Material(String materialType, boolean isMinable, int value, int weight) {
		this.materialType = materialType;
		this.isMinable = isMinable;
		this.value = value;
		this.weight = weight;
	}

	/**
	 * Gets the type of material.
	 * 
	 * @return The material type.
	 */
	public String getMaterialType() {
		return materialType;
	}

	/**
	 * Checks if the material is minable.
	 * 
	 * @return True if the material is minable, false otherwise.
	 */
	public boolean isMinable() {
		return isMinable;
	}

	/**
	 * Gets the value of the material.
	 * 
	 * @return The value of the material.
	 */
	public int getValue() {
		return value;
	}

	/**
	 * Gets the weight of the material.
	 * 
	 * @return The weight of the material.
	 */
	public int getWeight() {
		return weight;
	}

	/**
	 * Generates a random image view for the material.
	 * 
	 * @param type The type of image.
	 * @return The image view.
	 */
	public ImageView randomImageView(String type) {
		Random random = new Random();
		int randomInt = random.nextInt(1, 3);

		String path = "/assets/underground/" + type + ("_0" + randomInt + ".png");
		Image image = new Image(path);

		ImageView imageView = new ImageView(image);

		return imageView;
	}

	/**
	 * Gets the image view for the material.
	 * 
	 * @param type The type of image.
	 * @return The image view.
	 */
	public ImageView getImageView(String type) {
		String path = "/assets/underground/" + type + ".png";
		Image image = new Image(path);
		ImageView imageView = new ImageView(image);
		return imageView;
	}

	/**
	 * Generates a lava material.
	 * 
	 * @return The lava material.
	 */
	public static Material generateLava() {
		Material lava = new Material("lava", false, 0, 0);
		return lava;
	}

	/**
	 * Generates a random valuable material.
	 * 
	 * @return The valuable material.
	 */
	public static Material generateRandomMaterial() {
		Random random = new Random();
		String randomType = MATERIAL_TYPES[random.nextInt(MATERIAL_TYPES.length)];
		String materialType = "valuable_" + randomType;
		Material material = new Material(materialType, true, MATERIAL_MAP.get(randomType).get(0),
				MATERIAL_MAP.get(randomType).get(1));
		return material;
	}

	/**
	 * Creates a list containing material information.
	 * 
	 * @param value  The value of the material.
	 * @param weight The weight of the material.
	 * @return The list containing material information.
	 */
	private static List<Integer> createMaterialInfo(int value, int weight) {
		return Arrays.asList(value, weight);
	}
}