#pragma once
#include <SFML/Graphics.hpp>

namespace Scene
{
	void Initialize();
	void Draw(sf::RenderWindow&);
	void Animate(sf::RenderWindow&);

	void HandleKeyEvent(sf::Event);
	void HandleMouseEvent(sf::Event);

	sf::Color GetClearColor();
};
