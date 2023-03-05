#pragma once
enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT = 1, MOVING_RIGHT = 2, JUMPING, FALLING};
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	
	sf::Clock animationTimer;

	
	//Animation
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	//Core
	void initVariables();
	void initSprite();
	void initTexture();
	void initAnimations();
	void initPhysics();
public:
	Player();
	virtual ~Player();
	//Accessors
	const bool& getAnimSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	// Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();
	//Functions
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateAnimations();
	void updateMovement();
	void update();
	void render(sf::RenderTarget& target);
};

