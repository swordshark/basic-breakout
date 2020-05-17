#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Scene.h"
#include "Breakout.h"

namespace Scene
{
	// Declare Font and Text objects for "Press SPACE to Start", "Game Over" and "You Win" text
	sf::Font font;
	sf::Text win, gameStart, gameOver;
	bool start = true;
	int remainingBlocks = 40;

	// Declare Generator and Distribution objects for RNG
	std::default_random_engine generator;
	std::uniform_int_distribution<int> color(10, 250);
	std::uniform_int_distribution<int> direction(-1, 1);

	// Declare the objects to be animated and drawn
	Ball ball = Ball();
	Paddle paddle = Paddle();
	Block blocks[8][5];

	sf::Color sceneColor;

	sf::Color GetClearColor() {
		return sceneColor;
	}

	// Animation helper functions
	float length(sf::Vector2f a) {
		return sqrtf(a.x * a.x + a.y * a.y);
	}
	float dot(sf::Vector2f a, sf::Vector2f b) {
		return a.x * b.x + a.y * b.y;
	}

	void Initialize() {

		// Set background color to Black
		sceneColor = sf::Color::Black;

		// Load font from file, throw error message if fails
		if (!font.loadFromFile("Roboto-Medium.ttf")) {
			std::cout << "Could not load font." << std::endl;
		}

		// Initialize all text
		win.setFont(font);
		win.setString("YOU WIN!!");
		win.setCharacterSize(30);
		win.setFillColor(sf::Color::Green);
		win.setPosition(sf::Vector2f(300, 400));

		gameStart.setFont(font);
		gameStart.setString("Press SPACE to start!");
		gameStart.setCharacterSize(30);
		gameStart.setFillColor(sf::Color::Yellow);
		gameStart.setPosition(sf::Vector2f(250, 400));

		gameOver.setFont(font);
		gameOver.setString("GAME OVER...");
		gameOver.setCharacterSize(30);
		gameOver.setFillColor(sf::Color::Red);
		gameOver.setPosition(sf::Vector2f(325, 400));

		// Initialize all positions and colors of blocks
		sf::Color randC;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 5; j++) {
				randC = sf::Color((float)color(generator), (float)color(generator), (float)color(generator));
			
				blocks[i][j] = Block(sf::Vector2f((i * 100.0f) + 50, (j * 30.0f) + (j * 5.0f) + 50.0f), randC);
			}
		}
	}

	// Call Animate, Draw, and KeyEvent functions of other classes
	void Draw(sf::RenderWindow& window) {

		// Draw the Paddle and the Balls
		paddle.Draw(window);

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 5; j++) {
				if (blocks[i][j].getHit()) {
					blocks[i][j].Draw(window);
				}
			}
		}

		// Draw the Prompt to Start the Game
		if (start) {
			window.draw(gameStart);
		}

		// Draw either Game Over/Won text or Ball, depending if the Game is over or not
		if (ball.getGameOver() && remainingBlocks > 0) {
			window.draw(gameOver);
		}
		else if (remainingBlocks == 0) {
			window.draw(win);
		}
		else {
			ball.Draw(window);
		}
	}

	void Animate(sf::RenderWindow& window) {

		static sf::Clock clock;
		sf::Time elapsed = clock.restart(); //keep track of elapsed time
		float deltaTime = elapsed.asSeconds(); //this is the time since the last restart (time since last frame)

		if (!start) {
			ball.Animate(window, deltaTime);
			
			// Detect if ball collides with paddle
			if ((ball.mPosition.y + 15.0f > paddle.mPosition.y - 15.0f && ball.mPosition.y - 15.0f < paddle.mPosition.y + 15.0f) &&
				(ball.mPosition.x + 15.0f > paddle.mPosition.x - 50.0f && ball.mPosition.x - 15.0f < paddle.mPosition.x + 50.0f)) {

				ball.mPosition.y = paddle.mPosition.y - 30.0f;

				if (ball.mVelocity.y > 0.0f) {
					ball.mVelocity.y = -ball.mVelocity.y;
				}

				if (ball.mVelocity.x == 0.0f) {
					if (ball.mPosition.x >= paddle.mPosition.x) {
						ball.mVelocity.x = 100.0f;
					}
					else {
						ball.mVelocity.x = -100.0f;
					}
				}

				// Reacting to how the x velocity should behave
				if (ball.mPosition.x >= paddle.mPosition.x + 35.0f && ball.mVelocity.x < 0.0f ||
					ball.mPosition.x <= paddle.mPosition.x - 35.0f && ball.mVelocity.x > 0.0f) {
					ball.mVelocity.x = -ball.mVelocity.x;
				}
				else if (ball.mPosition.x >= paddle.mPosition.x - 10.0f && ball.mPosition.x <= paddle.mPosition.x + 10.0f) {
					ball.mVelocity.x = 0.0f;
				}
			}


			// Detect if ball collides with any and all blocks, block is "hit" and ball reflects properly
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 5; j++) {

					Block& b = blocks[i][j];

					if ((ball.mPosition.y + 15.0f > b.mPosition.y - 15.0f && ball.mPosition.y - 15.0f < b.mPosition.y + 15.0f) &&
						(ball.mPosition.x + 15.0f > b.mPosition.x - 50.0f && ball.mPosition.x - 15.0f < b.mPosition.x + 50.0f)) {

						// Decrement number of blocks "remaining"
						b.hit = false;
						remainingBlocks--;

						if (ball.mPosition.y > b.mPosition.y) {
							ball.mPosition.y = b.mPosition.y + 30.0f;

							if (ball.mVelocity.y < 0) {
								ball.mVelocity.y = -ball.mVelocity.y;
							}
						}
						else if (ball.mPosition.y < b.mPosition.y) {
							ball.mPosition.y = b.mPosition.y - 30.0f;

							if (ball.mVelocity.y > 0) {
								ball.mVelocity.y = -ball.mVelocity.y;
							}
						}				

						// Move discarded blocks
						b.mPosition = sf::Vector2f(-100.0f, -100.0f);
					}
				}
			}
		}
	}

	void HandleKeyEvent(sf::Event event) {
		if (start && event.key.code == sf::Keyboard::Space) {
			int d = direction(generator);

			switch (d) {
			case -1:
				ball.Start(sf::Vector2f(paddle.getPosition().x, paddle.getPosition().y - 60.0f), sf::Vector2f(-100.0f, -350.0));

			case 0:
				ball.Start(sf::Vector2f(paddle.getPosition().x, paddle.getPosition().y - 60.0f), sf::Vector2f(0.0f, -350.0));

			case 1:
				ball.Start(sf::Vector2f(paddle.getPosition().x, paddle.getPosition().y - 60.0f), sf::Vector2f(100.0f, -350.0));

			}
			
			start = false;
		}
	}

	void HandleMouseEvent(sf::Event event) {
		paddle.HandleMouseEvent(event);
	}
};