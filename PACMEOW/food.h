#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "Player.h"
#define FoodNumber path.size()

//#define FoodNumber 3
class Food
{
public:
	Food();
	~Food();
	//void Update();
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() { return OneBody.getPosition(); }
	//std::vector<sf::RectangleShape> body{FoodNumber};
	std::vector<sf::Sprite> body{ FoodNumber };
	bool CheckTexture(sf::Sprite OneFood, sf::Texture& tex);
	sf::Texture texture[9];
private:
	int maxFood[9] = { 0,0,0,0,10,30,10,30,30 };
	sf::Clock countTimeSpeed;
	bool startScoreBoost;
	int countFood[9] = {};
	int scoreBoost = 1;
	//sf::Texture ghostTexture;
	sf::RectangleShape OneBody;
};

