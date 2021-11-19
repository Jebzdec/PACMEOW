#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "State.h"
class Leaderboard
{
public:
	Leaderboard(sf::View& view);
	~Leaderboard();
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
	sf::Text rankScore[5];
	sf::Text rankName[5];
};

