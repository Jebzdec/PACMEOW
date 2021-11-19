#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "State.h"
#define MAX_ITEMS 4
class Menu
{
public:
	Menu(sf::View& view);
	~Menu();
	void Draw(sf::RenderWindow& window, sf::View& view);
	void MoveUp();
	void MoveDown();
	void Event(sf::RenderWindow& window, sf::Event event);
	int GetPressedItem() { return selectedItem; }
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;
	int selectedItem = 0;
	sf::Font font;
	sf::Text menu[MAX_ITEMS]; //start leaderboard exit
};

