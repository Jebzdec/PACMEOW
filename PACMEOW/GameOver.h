#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "State.h"
class GameOver
{
public:
	GameOver(sf::View& view);
	~GameOver();
	void Update(sf::View& view);
	void Draw(sf::RenderWindow& window, sf::View& view);
	void Event(sf::RenderWindow& window, sf::Event event);
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Font font;
	sf::Text text; //start leaderboard exit
};

