#include "stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "Dodge it", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(144);
}

void Game::initPlayer()
{
	this->player = new Player();
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();

}

Game::~Game()
{
	delete this->player;
}

void Game::updateCollision()
{
	//Colission bottom on of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{

		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height);
	}
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::update()
{
	//Polling window evennts
	while (this->window.pollEvent(this->ev)) 
	{
		if (this->ev.type == sf::Event::Closed) 
		{	
			this->window.close();
		}
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) 
		{
			this->window.close();
		}
		if (this->ev.type == sf::Event::KeyReleased &&
			(this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::S))
		{
			this->player->resetAnimationTimer();
		}
	}
	this->updatePlayer();
	this->updateCollision();
}

void Game::render()
{

	this->window.clear(sf::Color::White);
	this->player->render(this->window);
	
	//Render game
	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	// TODO: вставьте здесь оператор return
	return this->window;
}
