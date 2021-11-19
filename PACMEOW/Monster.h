#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Emotion.h"
#define MonsterNumber 4 //per quadrant

class Monster
{
public:
	Monster(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Monster();

	//void Update(float deltaTime, bool press);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return OneBody.getPosition(); }
	Animation animation;
	std::vector<sf::RectangleShape> body[5];//quadrant

	int RandDir[5][MonsterNumber] = {};
	unsigned int countWalk[5][MonsterNumber];
	unsigned int MaxWalk[5][MonsterNumber];
	int direction[4][2] = { {-1,0}, {0,-1},{0,1},{1,0} };
	unsigned int row[5][MonsterNumber];//bodysize = monstersize
	float speed;
private:
	sf::RectangleShape OneBody;
};

