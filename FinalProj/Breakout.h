#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"

// Blocks broken in Breakout game
class Block {

protected:
	sf::RectangleShape mShape;
	sf::Vector2f mPosition;
	bool hit;

public:
	Block();
	Block(sf::Vector2f, sf::Color);
	void Draw(sf::RenderWindow&);
	bool getHit();
	void setHit(bool h);

	friend void Scene::Animate(sf::RenderWindow&);
};

// Ball used to break blocks
class Ball {

protected:
	sf::CircleShape mCircle;
	sf::Vector2f mPosition;
	sf::Vector2f mVelocity;
	bool gameOver;

public:
	Ball();
	void Start(sf::Vector2f pos, sf::Vector2f vel);
	void Draw(sf::RenderWindow&);
	void Animate(sf::RenderWindow&, float deltaTime);
	sf::Vector2f getPosition();
	bool getGameOver();

	friend void Scene::Animate(sf::RenderWindow&);
};

// Paddle controlled by the player
class Paddle {
protected:
	sf::RectangleShape mShape;
	sf::Vector2f mPosition;

public:
	Paddle();
	void Draw(sf::RenderWindow&);
	void HandleMouseEvent(sf::Event event);
	sf::Vector2f getPosition();

	friend void Scene::Animate(sf::RenderWindow&);
};