#include "stdafx.h"
#include "Player.h"



void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	
	
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 64, 80);
	this->sprite.setTextureRect(sf::IntRect(this->currentFrame));
	this->sprite.setScale(2, 2);


}


void Player::initTexture()
{
	
	if (!this->textureSheet.loadFromFile("Textures/1.png"))
	{
		std::cout << "ERROR::PLAYER:: could not load the player sheet " << std::endl;
	}
	else
	{
		std::cout << "file" << std::endl;
	}
}

void Player::initAnimations()
{

	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 5.f;
	this->acceleration = 3.f;
	this->drag = 0.85f;
	this->velocityMin = 2.f;
	this->gravity = 4.f;
	this->velocityMaxY = 15.f;
}

Player::Player()
{
	
	this->initVariables();
	this->initAnimations();
	this->initTexture();
	this->initSprite();
	this->initPhysics();
}

Player::~Player()
{

}

const bool& Player::getAnimSwitch()
{
	// TODO: вставьте здесь оператор return
	bool anim_switch = this->animationSwitch;
	if (this->animationSwitch) 
	{
		this->animationSwitch = false;
	}
	return anim_switch;
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}


void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	//Acceleration
	this->velocity.x += dir_x * this->acceleration;
	this->velocity.y += -2 * this->gravity;
	
	
	//Limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}



void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1 * this->gravity; 
	std::cout << velocity.y<< std::endl;
	
	this->sprite.move(this->velocity);
}

void Player::updateAnimations() // idle animations
{
	
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.15f || this->getAnimSwitch()) 
		{
			this->currentFrame.top = 635.f;
			this->currentFrame.left += 80.f;
			if (this->currentFrame.left >= 500.f)
			{
				this->currentFrame.left = 0.f;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT) 
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.01f)
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 80.f;
			if (this->currentFrame.left >= 500.f)
			{
				this->currentFrame.left = 0.f;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			
		}
		this->sprite.setScale(2.f, 2.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.01f)
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 80.f;
			if (this->currentFrame.left >= 500.f)
			{
				this->currentFrame.left = 0.f;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			this->sprite.setScale(-2.f, 2.f);
		}
		this->sprite.setScale(-2.f, 2.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 1.1f, 0.f);
	}

}

void Player::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //left
	{
		this->move(-3.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //right
	{
		this->move(3.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) //right
	{
		
		this->move(0, -10);

	}
	
		
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) //top
	//{
	//	this->sprite.move(0.f, -3.f);
	//	
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) //down
	//{
	//	this->sprite.move(0.f, 3.f);
	//	
	//}


}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(2.f);
	circ.setPosition(this->sprite.getPosition());
	target.draw(circ);
}
