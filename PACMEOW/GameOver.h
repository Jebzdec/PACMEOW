#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "State.h"
class GameOver
{
public:
	GameOver(sf::View& view);
	~GameOver();
	void Update(sf::View& view, unsigned long  sc);
	void Draw(sf::RenderWindow& window, sf::View& view);
	void Event(sf::RenderWindow& window, sf::Event event);
	sf::Music effLose;
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Font font;
	sf::Text score; //start leaderboard exit
};

