#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scene.h"


int main() {

	// Create the standard 800 x 800 window
	sf::RenderWindow window(sf::VideoMode(800, 800), "Final Project, Dominic Bourassa");

	// Initialize scene
	Scene::Initialize();

	// Run the program as long as the window is open
	while (window.isOpen()) {

		// Check for events that were triggered during the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event)) {

			// Check events in the Scene
			if (event.type == sf::Event::KeyPressed) {
				Scene::HandleKeyEvent(event);
			}

			if (event.type == sf::Event::MouseMoved) {
				Scene::HandleMouseEvent(event);
			}

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Clear the window, animate the scene, then draw the scene
		window.clear(Scene::GetClearColor());
		Scene::Animate(window);
		Scene::Draw(window);

		// End current frame
		window.display();
	}

	return 0;
}