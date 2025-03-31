

import java.text.DecimalFormat;
import java.util.Locale;
import java.util.Random;

import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.text.Text;
import javafx.util.Duration;

public class DrillMachine {
	private int x, y; // Position of the drill machine
	protected static boolean isFlying;
	private double fuelValue;
	protected static boolean isMoving;
	private int haulWeight = 0;
	private int money = 0;
	private Direction direction;
	private ImageView imageView; // ImageView to display the drill machine
	private Image[] assetImages; // Array to hold different images for different directions

	public DrillMachine(int x, int y) {
		Random random = new Random();
		this.x = x;
		this.y = y;
		this.fuelValue = random.nextDouble(7000, 10000);
		this.direction = Direction.RIGHT; // Initial direction
		loadAssets(); // Load the assets for different directions
		this.imageView = new ImageView(assetImages[direction.ordinal()]);
		this.imageView.setFitHeight(55);
		this.imageView.setFitWidth(55);
		this.imageView.setX(x * Game.TILE_SIZE); // Assuming Tile.SIZE is the size of each tile
		this.imageView.setY(y * Game.TILE_SIZE);
	}

	public void move(Direction direction) {
		String objTypeAbove = Game.objectMap.getMaterial(getY() - 1, getX()).getMaterialType();
		// Adjust position based on the direction
		switch (direction) {
		case UP:
			System.out.println("up");
			if (!Game.GAME_OVER) {
				if ((objTypeAbove.equals("empty") || objTypeAbove.equals("sky")) && y > 0) {
					isFlying = true;
					Game.objectMap.removeDrillMachine(getY(), getX());
					y--;
					this.direction = Direction.UP;
				}
				break;
			}
		case DOWN:
			System.out.println("down");
			if (!Game.GAME_OVER && !isFlying) {
				if (Game.objectMap.getMaterial(getY() + 1, getX()).isMinable()) {
					Game.objectMap.removeDrillMachine(getY(), getX());
					isMoving = true;
					y++;
					this.direction = Direction.DOWN;
					money += Game.objectMap.getMaterial(getY(), getX()).getValue();
					haulWeight += Game.objectMap.getMaterial(getY(), getX()).getWeight();
					if (!(Game.objectMap.getMaterial(getY(), getX()).getMaterialType().equals("empty")
							|| Game.objectMap.getMaterial(getY(), getX()).getMaterialType().equals("sky"))) {
						Game.objectMap.removeMaterial(getY(), getX());
						Game.removeMaterialFromMap(Game.gameMap, getY(), getX());
					}
					break;
				} else if (Game.objectMap.getMaterial(getY() + 1, getX()).getMaterialType().equals("lava")) {
					Game.lavaGameOver();
				} else {
					break;
				}
			}
		case LEFT:
			System.out.println("left");
			if (!Game.GAME_OVER && !isFlying) {
				if (Game.objectMap.getMaterial(getY(), getX() - 1).isMinable()) {
					Game.objectMap.removeDrillMachine(getY(), getX());
					isMoving = true;
					x--;
					this.direction = Direction.LEFT;
					money += Game.objectMap.getMaterial(getY(), getX()).getValue();
					haulWeight += Game.objectMap.getMaterial(getY(), getX()).getWeight();
					if (!(Game.objectMap.getMaterial(getY(), getX()).getMaterialType().equals("empty")
							|| Game.objectMap.getMaterial(getY(), getX()).getMaterialType().equals("sky"))) {
						Game.objectMap.removeMaterial(getY(), getX());
						Game.removeMaterialFromMap(Game.gameMap, getY(), getX());
					}
					break;
				} else if (Game.objectMap.getMaterial(getY(), getX() - 1).getMaterialType().equals("lava")) {
					Game.lavaGameOver();
				} else {
					break;
				}
			}
		case RIGHT:
			System.out.println("right");
			if (!Game.GAME_OVER && !isFlying) {
				if (Game.objectMap.getMaterial(getY(), getX() + 1).isMinable()) {
					Game.objectMap.removeDrillMachine(getY(), getX());
					isMoving = true;
					x++;
					this.direction = Direction.RIGHT;
					money += Game.objectMap.getMaterial(getY(), getX()).getValue();
					haulWeight += Game.objectMap.getMaterial(getY(), getX()).getWeight();
					if (!(Game.objectMap.getMaterial(getY(), getX()).getMaterialType().equals("empty")
							|| Game.objectMap.getMaterial(getY(), getX()).getMaterialType().equals("sky"))) {
						Game.objectMap.removeMaterial(getY(), getX());
						Game.removeMaterialFromMap(Game.gameMap, getY(), getX());
					}
					break;
				} else if (Game.objectMap.getMaterial(getY(), getX() + 1).getMaterialType().equals("lava")) {
					Game.lavaGameOver();
				} else {
					break;
				}
			}
		}
		changeAsset();
	}

	public void applyGravity() {
		Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(0.4), e -> {
			String objTypeBelow = Game.objectMap.getMaterial((int) Math.ceil(getY()) + 1, getX()).getMaterialType();
			if (!Game.GAME_OVER && (objTypeBelow.equals("sky") || objTypeBelow.equals("empty"))) {
				Game.objectMap.removeDrillMachine(y, x);
				y += 1 + (haulWeight * 0.001);
			}
		}));
		timeline.setCycleCount(Animation.INDEFINITE);
		timeline.play();
		if (Game.GAME_OVER) {
			timeline.stop();
		}
	}

	private void changeAsset() {
		imageView.setImage(assetImages[direction.ordinal()]);
	}

	private void loadAssets() {
		String path = "/assets/drill/";
		assetImages = new Image[Direction.values().length];
		assetImages[Direction.UP.ordinal()] = new Image(path + "drill_up.png");
		assetImages[Direction.DOWN.ordinal()] = new Image(path + "drill_down.png");
		assetImages[Direction.LEFT.ordinal()] = new Image(path + "drill_left.png");
		assetImages[Direction.RIGHT.ordinal()] = new Image(path + "drill_right.png");
	}

	public void updateFuel(Text fuelText) {
		Locale.setDefault(new Locale("en", "US"));
		DecimalFormat df = new DecimalFormat("#.##");
		Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(0.03), e -> {
			if (!Game.GAME_OVER) {
				if (fuelValue > 0) {
					if (isMoving) {
						fuelValue -= 40.42;
					} else if (isFlying) {
						fuelValue -= haulWeight * 0.72;
					} else {
						fuelValue -= 0.53;
					}
					fuelText.setText(df.format(fuelValue));
				} else {
					fuelValue = 0;
					fuelText.setText(df.format(fuelValue));
					Game.gameOver();
				}
			}
		}));
		timeline.setCycleCount(Animation.INDEFINITE);
		timeline.play();
		if (Game.GAME_OVER) {
			timeline.stop();
		}

	}

	public void updateHaulWeight(Text haulText) {
		Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(0.03), e -> {
			haulText.setText(haulWeight + "");
		}));
		timeline.setCycleCount(Animation.INDEFINITE);
		timeline.play();
	}

	public void updateMoney(Text moneyText) {
		Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(0.03), e -> {
			moneyText.setText(money + "");
		}));
		timeline.setCycleCount(Animation.INDEFINITE);
		timeline.play();
	}

	// Getters and Setters

	public ImageView getImageView() {
		return imageView;
	}

	public double getFuelValue() {
		return fuelValue;
	}

	public int getMoney() {
		return money;
	}

	public int getHaulWeight() {
		return haulWeight;
	}

	public int getX() {
		return x;
	}

	public DrillMachine getDrillMachine() {
		return this;
	}

	public int getY() {
		return y;
	}

	public Direction getDirection() {
		return direction;
	}

}

// Enum to represent different directions
enum Direction {
	UP, DOWN, LEFT, RIGHT
}