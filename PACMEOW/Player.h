#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <iostream>
#include "Map.h"
#include "Monster.h"/*
extern sf::Vector2f posPlayer;
extern int health;
extern float speed;
extern bool bonusSpeed;
extern int emo;*/
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	//void Update(float deltaTime,bool press);
	void Draw(sf::RenderWindow& window);

	Animation animation;
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::RectangleShape body;
	unsigned int row;
	float speed;
	bool bonusSpeed;

private:
	sf::Clock countTimeSpeed;
	sf::Time time;
};

