#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
class Emotion
{
public:
	Emotion();
	~Emotion();/*
	void Update(float deltaTime,int i,int x,int y);*/
	void Draw(sf::RenderWindow& window, int i);
	Animation* animation;
	sf::RectangleShape emotion[10];
	sf::Texture emotionTexture[10];
	int row[10];
};

