package assignment3;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Random;

import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.util.Duration;

/**
 * The Game class represents the main game application.
 */
public class Game extends Application {

	protected static final int MAP_ROWS = 16;
	protected static final int MAP_COLS = 14;
	protected static final int TILE_SIZE = 55;
	private static final int SCENE_WIDTH = 770;
	private static final int SCENE_HEIGHT = 880;
	private static List<String> materialTypeList = new ArrayList<>();
	public static boolean GAME_OVER = false;

	static GridPane gameMap;
	protected static ObjectMap objectMap = new ObjectMap();
	private static DrillMachine drillMachine;
	private static Scene scene;
	protected static Pane root;

	/**
	 * The main entry point for the application.
	 * 
	 * @param primaryStage The primary stage for this application.
	 */
	@Override
	public void start(Stage primaryStage) {
		root = new Pane();
		root.setPrefSize(SCENE_WIDTH, SCENE_HEIGHT);
		// Create the game map and object map
		gameMap = createMapGrid();
		populateMap(gameMap);

		// Set background color of the game map
		gameMap.setBackground(new Background(new BackgroundFill(Color.DARKSLATEBLUE, null, null)));

		// Create VBox for layout
		VBox vbox = new VBox(gameMap);
		vbox.setAlignment(Pos.BOTTOM_CENTER);

		// Create the scene with the VBox
		scene = new Scene(new Pane(vbox), MAP_COLS * TILE_SIZE, MAP_ROWS * TILE_SIZE);
		scene.setOnKeyPressed(this::handleKeyPress);

		// Add fuel, haul, and money text
		drillMachine = new DrillMachine(6, 2);
		addText((Pane) scene.getRoot(), "fuel:", 5, 30);
		Text fuelText = addText((Pane) scene.getRoot(), String.valueOf(drillMachine.getFuelValue()), 60, 30);
		drillMachine.updateFuel(fuelText);
		addText((Pane) scene.getRoot(), "haul:", 5, 60);
		Text haulText = addText((Pane) scene.getRoot(), String.valueOf(drillMachine.getHaulWeight()), 70, 60);
		drillMachine.updateHaulWeight(haulText);
		addText((Pane) scene.getRoot(), "money:", 5, 90);
		Text moneyText = addText((Pane) scene.getRoot(), String.valueOf(drillMachine.getMoney()), 105, 90);
		drillMachine.updateMoney(moneyText);
		updateDrillMachinePosition(gameMap);

		// Set the scene and stage properties
		primaryStage.setScene(scene);
		primaryStage.setTitle("HU-Loader");
		primaryStage.show();
	}

	/**
	 * Creates a grid pane representing the game map.
	 * 
	 * @return The created grid pane.
	 */
	private GridPane createMapGrid() {
		GridPane grid = new GridPane();
		return grid;
	}

	/**
	 * Adds a text node to the specified root pane with the given text and position.
	 * 
	 * @param root      The root pane to which the text node will be added.
	 * @param stringTxt The text content.
	 * @param pos1      The x-coordinate position.
	 * @param pos2      The y-coordinate position.
	 * @return The created text node.
	 */
	private Text addText(Pane root, String stringTxt, double pos1, double pos2) {
		Text text = new Text(stringTxt);
		text.setFill(Color.WHITE);
		text.setFont(Font.font(30));
		text.setLayoutX(pos1); // Set layout X coordinate relative to the root Pane
		text.setLayoutY(pos2); // Set layout Y coordinate relative to the root Pane
		root.getChildren().add(text);
		return text; // Return the created Text node
	}

	/**
	 * Determines if the tile at the specified row and column should have a border
	 * boulder.
	 * 
	 * @param map The game map grid pane.
	 * @param row The row index.
	 * @param col The column index.
	 * @return True if the tile should have a border boulder, false otherwise.
	 */
	private boolean borderBoulder(GridPane map, int row, int col) {
		if ((row >= 4 && (col == 13 || col == 0)) || row == 15) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Populates the game map grid pane with tiles and materials.
	 * 
	 * @param map The game map grid pane.
	 */
	private void populateMap(GridPane map) {
		int soilCount = 0;
		int materialCount = 0;
		Map<String, List<Integer>> materialMap = Material.MATERIAL_MAP;
		for (int row = 0; row < MAP_ROWS; row++) {
			for (int col = 0; col < MAP_COLS; col++) {
				Rectangle tile = new Rectangle(TILE_SIZE, TILE_SIZE);
				Material sky = new Material("sky", true, 0, 0);

				// Determine tile color based on row
				Color tileColor = (row < 3) ? Color.DARKSLATEBLUE : Color.CHOCOLATE;
				Material material = (row < 3) ? sky : null;

				// Adjust tile size and position for specific rows
				if (row == 2) {
					tile.setHeight(TILE_SIZE + 7);
				} else if (row == 3) {
					tile.setHeight(TILE_SIZE - 7);
				}
				objectMap.addMaterial(row, col, material);
				tile.setFill(tileColor);
				map.add(tile, col, row);

				// Add topSoil image at row 3
				if (row == 3) {
					Material topSoil = new Material("soil", true, 0, 0);
					objectMap.addMaterial(row, col, topSoil);
					ImageView imageView = topSoil.randomImageView("top");
					imageView.setFitWidth(TILE_SIZE);
					imageView.setFitHeight(TILE_SIZE);
					map.add(imageView, col, row);
					soilCount++;
				}
				if (borderBoulder(map, row, col)) {
					Material boulder = new Material("boulder", false, 0, 0);
					objectMap.addMaterial(row, col, boulder);
					ImageView imageView = boulder.randomImageView("obstacle");
					imageView.setFitWidth(TILE_SIZE);
					imageView.setFitHeight(TILE_SIZE);
					map.add(imageView, col, row);
					soilCount++;

				}
				if (row > 3 && !borderBoulder(map, row, col)) { 
					Material soil = new Material("soil", true, 0, 0);
					objectMap.addMaterial(row, col, soil);
					ImageView imageView = soil.randomImageView("soil");
					imageView.setFitWidth(TILE_SIZE);
					imageView.setFitHeight(TILE_SIZE);
					map.add(imageView, col, row);
					soilCount++;
				}
			}
		}

		// populate the map with the valuable materials and lava
		List<List<Integer>> materialPlacementList = new ArrayList<>();
		materialTypeList = populateMaterialTypeList();

		Random random = new Random();
		while (soilCount - random.nextInt(100, 120) > materialCount) {
			int randomCol = random.nextInt(1, 13);
			int randomRow = random.nextInt(4, 15);
			String randomMaterialType = materialTypeList.get(random.nextInt(materialTypeList.size()))
					.replace("valuable_", "");
			int matValue = materialMap.get(randomMaterialType).get(0);
			int matWeight = materialMap.get(randomMaterialType).get(1);
			boolean containsRowAndCol = materialPlacementList.stream()
					.anyMatch(innerList -> innerList.contains(randomRow) && innerList.contains(randomCol));
			if (!containsRowAndCol) {
				// Check if this position should have lava
				boolean shouldHaveLava = random.nextBoolean();
				if (shouldHaveLava) {
					Material lava = Material.generateLava();
					objectMap.addMaterial(randomRow, randomCol, lava);
					ImageView lavaImage = lava.randomImageView("lava");
					lavaImage.setFitWidth(TILE_SIZE);
					lavaImage.setFitHeight(TILE_SIZE);
					materialCount++;
					soilCount--;
					List<Integer> rowsAndCols = new ArrayList<>();
					rowsAndCols.add(randomRow);
					rowsAndCols.add(randomCol);
					materialPlacementList.add(rowsAndCols);
					map.add(lavaImage, randomCol, randomRow);
				} else {
					Material material = new Material(randomMaterialType, true, matValue, matWeight);
					objectMap.addMaterial(randomRow, randomCol, material);
					materialCount++;
					soilCount--;
					ImageView image = material.getImageView("valuable_" + randomMaterialType);
					image.setFitWidth(TILE_SIZE);
					image.setFitHeight(TILE_SIZE);
					List<Integer> rowsAndCols = new ArrayList<>();
					rowsAndCols.add(randomRow);
					rowsAndCols.add(randomCol);
					materialPlacementList.add(rowsAndCols);
					map.add(image, randomCol, randomRow);
				}
			}
		}
		System.out.println(objectMap.mapToString());

	}

	// create a corresponding 2D object map so can determine variables

	private List<String> populateMaterialTypeList() {
		Random random = new Random();
		while (materialTypeList.size() != random.nextInt(3, 7)) {
			Material material = Material.generateRandomMaterial();
			if (!materialTypeList.contains(material.getMaterialType()))
				materialTypeList.add(material.getMaterialType());
		}
		return materialTypeList;
	}

	/**
	 * Updates the position of the drill machine on the game map.
	 * 
	 * @param map The game map grid pane.
	 */
	private void updateDrillMachinePosition(GridPane map) {
		Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(0.01), e -> {
			// Update the position of the drill machine
			if (!GAME_OVER) {
				map.getChildren().remove(drillMachine.getImageView());
				drillMachine.getImageView().setX(drillMachine.getX() * TILE_SIZE);
				drillMachine.getImageView().setY(drillMachine.getY() * TILE_SIZE);
				objectMap.addDrillMachine(drillMachine.getY(), drillMachine.getX(), drillMachine);
				map.add(drillMachine.getImageView(), drillMachine.getX(), drillMachine.getY());
				DrillMachine.isMoving = false;
				DrillMachine.isFlying = false;
			}
		}));
		drillMachine.applyGravity();
		timeline.setCycleCount(Animation.INDEFINITE);
		timeline.play();
		if (GAME_OVER) {
			timeline.stop();
		}
	}

	/**
	 * Handles the key press events for controlling the drill machine.
	 * 
	 * @param event The key event.
	 */
	private void handleKeyPress(KeyEvent event) {
		KeyCode keyCode = event.getCode();
		switch (keyCode) {
		case UP:
			// Handle up key press
			drillMachine.move(Direction.UP);
			break;
		case DOWN:
			// Handle down key press
			drillMachine.move(Direction.DOWN);
			break;
		case LEFT:
			// Handle left key press
			drillMachine.move(Direction.LEFT);
			break;
		case RIGHT:
			// Handle right key press
			drillMachine.move(Direction.RIGHT);
			break;
		case E:
			System.out.println(objectMap.mapToString());
		default:
			break;
		}
	}

	/**
	 * Displays the game over message when the drill machine encounters lava.
	 */
	public static void lavaGameOver() {
		// Create game over message
		Text gameOverText = new Text("GAME OVER");
		gameOverText.setFont(Font.font(70));
		gameOverText.setFill(Color.WHITE);

		StackPane gameOverPane = new StackPane();
		gameOverPane.setBackground(new Background(new BackgroundFill(Color.RED, null, null)));
		gameOverPane.getChildren().add(gameOverText);
		gameOverPane.setAlignment(Pos.CENTER);
		gameOverPane.setPrefSize(SCENE_WIDTH, SCENE_HEIGHT);

		// Add game over pane to root
		scene.setRoot(root);
		root.getChildren().addAll(gameOverPane);
		GAME_OVER = true;

	}

	/**
	 * Displays the game over message along with the collected money.
	 */
	public static void gameOver() {
		// Create game over message
		Text gameOverText = new Text("GAME OVER");
		gameOverText.setFont(Font.font(70));
		gameOverText.relocate(190, 330);
		gameOverText.setFill(Color.WHITE);
		Text moneyText = new Text("Collected Money:" + drillMachine.getMoney());
		moneyText.setFont(Font.font(30));
		moneyText.relocate(230, 430);
		moneyText.setFill(Color.WHITE);

		Pane gameOverPane = new Pane();
		gameOverPane.setBackground(new Background(new BackgroundFill(Color.GREEN, null, null)));
		gameOverPane.setPrefSize(SCENE_WIDTH, SCENE_HEIGHT);
		gameOverPane.getChildren().addAll(moneyText, gameOverText);

		// Add game over pane to root
		scene.setRoot(root);
		root.getChildren().addAll(gameOverPane);
		GAME_OVER = true;
	}

	/**
	 * Removes the material from the specified row and column on the game map.
	 * 
	 * @param map The game map grid pane.
	 * @param row The row index.
	 * @param col The column index.
	 */
	public static void removeMaterialFromMap(GridPane map, int row, int col) {
		// Get the index of the top-most child in the specified cell

		// Remove the ImageView from the specified cell
		Rectangle tile = new Rectangle(TILE_SIZE, TILE_SIZE);
		tile.setFill(Color.CHOCOLATE);
		map.add(tile, col, row);
		// Update the object map accordingly
		objectMap.removeMaterial(row, col);

	}
}
