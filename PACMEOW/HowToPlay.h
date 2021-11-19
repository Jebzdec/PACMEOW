#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "State.h"
class HowToPlay
{
public:
	HowToPlay(sf::View& view);
	~HowToPlay();

	void Draw(sf::RenderWindow& window, sf::View& view);
	void Event(sf::RenderWindow& window, sf::Event event);
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;
};

