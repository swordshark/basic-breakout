#include <SFML/Graphics.hpp>
#include <iostream>
#include "Breakout.h"

// Paddle Constructor and related Functions
Paddle::Paddle() {

	mPosition = sf::Vector2f(400.0f, 725.0f);

	mShape.setSize(sf::Vector2f(100.0f, 30.0f));
	mShape.setFillColor(sf::Color::White);
	mShape.setOrigin(sf::Vector2f(50.0f, 15.0f));
	mShape.setPosition(mPosition);
}

void Paddle::Draw(sf::RenderWindow& window) {
	window.draw(mShape);
}

void Paddle::HandleMouseEvent(sf::Event event) {

	if (event.type == sf::Event::MouseMoved) {
		mPosition.x = event.mouseMove.x;
	}

	mShape.setPosition(mPosition);
}

sf::Vector2f Paddle::getPosition() {
	return mPosition;
}

// Ball Constructor and related Functions
Ball::Ball() {

	const float radius = 15.0f;
	mCircle = sf::CircleShape(radius, 8);
	mCircle.setOrigin(7.5f, 7.5f);

	mPosition = sf::Vector2f(-30.0f, -30.0f);
	mVelocity = sf::Vector2f(0.0f, 0.0f);

	mCircle.setFillColor(sf::Color(250, 250, 250));

	gameOver = false;
}

void Ball::Draw(sf::RenderWindow& window) {
	window.draw(mCircle);
}

void Ball::Animate(sf::RenderWindow& window, float deltaTime) {

	// Update Position based on Velocity and Time
	mPosition += mVelocity * deltaTime;
	mCircle.setPosition(mPosition);

	// Detect and react to collisions made by the ball
	float ceiling = 0.0f;
	if (mPosition.y - 15.0f < ceiling) {
		mPosition.y = ceiling + 15.0f;

		if (mVelocity.y < 0.0f) {
			mVelocity.y = -mVelocity.y;
		}
	}

	// Game Over Condition, Game Ends as Ball falls offscreen
	float floor = window.getSize().y;
	if (mPosition.y - 15.0f > floor) {
		gameOver = true;
	}

	float wallL = 0.0f;
	if (mPosition.x - 15.0f < wallL) {
		mPosition.x = wallL + 15.0f;

		if (mVelocity.x < 0.0f) {
			mVelocity.x = -mVelocity.x;
		}
	}

	float wallR = window.getSize().x;
	if (mPosition.x - 15.0f > wallR) {
		mPosition.x = wallR - 15.0f;

		if (mVelocity.x > 0.0f) {
			mVelocity.x = -mVelocity.x;
		}
	}
}

void Ball::Start(sf::Vector2f pos, sf::Vector2f vel) {
	
	mPosition = pos;
	mVelocity = vel;

	mCircle.setPosition(pos);
}

sf::Vector2f Ball::getPosition() {
	return mPosition;
}

bool Ball::getGameOver() {
	return gameOver;
}

// Block Constructor and related Functions
Block::Block() {

	// Default constructor exists to create blocks before startup

	hit = true;
}

Block::Block(sf::Vector2f pos, sf::Color color) {

	mPosition = pos;

	mShape.setSize(sf::Vector2f(100.0f, 30.0f));
	mShape.setOrigin(sf::Vector2f(50.0f, 15.0f));
	mShape.setPosition(pos);
	mShape.setFillColor(color);
	hit = true;
}

void Block::Draw(sf::RenderWindow& window) {
	if (hit) {
		window.draw(mShape);
	}
}

bool Block::getHit() {
	return hit;
}

void Block::setHit(bool h) {
	hit = h;
}