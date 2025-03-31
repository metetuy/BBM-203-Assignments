

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;

import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

public class Material {
	private String materialType;
	private boolean isMinable;
	private int value;
	private int weight;

	private static final String[] MATERIAL_TYPES = { "ironium", "bronzium", "diamond", "emerald", "platinum",
			"goldium" };

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

	public Material(String materialType, boolean isMinable, int value, int weight) {
		this.materialType = materialType;
		this.isMinable = isMinable;
		this.value = value;
		this.weight = weight;
	}

	public String getMaterialType() {
		return materialType;
	}

	public boolean isMinable() {
		return isMinable;
	}


	public int getValue() {
		return value;
	}

	public int getWeight() {
		return weight;
	}

	public ImageView randomImageView(String type) {
		Random random = new Random();
		int randomInt = random.nextInt(1, 3);

		String path = "/assets/underground/" + type + ("_0" + randomInt + ".png");
		Image image = new Image(path);

		ImageView imageView = new ImageView(image);

		return imageView;
	}

	public ImageView getImageView(String type) {
		String path = "/assets/underground/" + type + ".png";
		Image image = new Image(path);
		ImageView imageView = new ImageView(image);
		return imageView;
	}

	// create lava
	public static Material generateLava() {
		Material lava = new Material("lava", false, 0, 0);
		return lava;

	}

	// add the valueable materials
	public static Material generateRandomMaterial() {
		Random random = new Random();
		String randomType = MATERIAL_TYPES[random.nextInt(MATERIAL_TYPES.length)];
		String materialType = "valuable_" + randomType;
		Material material = new Material(materialType, true, MATERIAL_MAP.get(randomType).get(0),
				MATERIAL_MAP.get(randomType).get(1));
		return material;

	}

	private static List<Integer> createMaterialInfo(int value, int weight) {
		return Arrays.asList(value, weight);
	}
}
