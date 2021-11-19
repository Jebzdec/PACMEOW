#pragma once
#include "Food.h"
#define bodyWidth 6
#define bodyHigh 4
Food::Food()
{
	texture[0].loadFromFile("picture/food/sushi1.png");
	texture[1].loadFromFile("picture/food/sushi2.png");
	texture[2].loadFromFile("picture/food/sushi3.png");
	texture[3].loadFromFile("picture/food/sushi4.png");
	texture[4].loadFromFile("picture/food/health.png");
	texture[5].loadFromFile("picture/food/speedBoost.png");
	texture[6].loadFromFile("picture/food/scoreBoost.png");
	texture[7].loadFromFile("picture/food/poison.png");
	texture[8].loadFromFile("picture/food/beer.png");
	std::fill(countFood, countFood + 9, 0);
	body.resize(FoodNumber);
	for (int i = 0; i < FoodNumber; i++)
	{
		body[i].setScale(0.3, 0.3);
		body[i].setPosition(path[i].first * 16 + 8, path[i].second * 16 + 8);
		int randNum = rand() % 100;
		int Rand = rand() % 9;
		randNum >= 85 ? Rand = rand() % 9 : Rand = rand() % 4;
		while (countFood[Rand] > maxFood[Rand] and maxFood[Rand] > 0) {
			Rand = rand() % 9;
		}
		body[i].setTexture(texture[Rand]);
		body[i].setOrigin(texture[Rand].getSize().x / 2, texture[Rand].getSize().y / 2);
		countFood[Rand]++;
	}
	startScoreBoost = false;
}
Food::~Food()
{
}

//void Food::Update()
//{
//	std::vector<int> Delete;
//	if (scoreBoost == 2) {
//		if (startScoreBoost == true)
//		{
//			countTimeSpeed.restart().asSeconds();
//			startScoreBoost = false;
//		}
//		if (countTimeSpeed.getElapsedTime() >= sf::seconds(10))
//		{
//			scoreBoost = 1;
//		}
//	}
//	for (int i = 0; i < body.size(); i++)
//	{
//		sf::Vector2f pos = body[i].getPosition();
//		float RecX[4] = { pos.x - body[i].getGlobalBounds().width / 2 ,
//			pos.x + body[i].getGlobalBounds().width / 2 ,
//			pos.x - body[i].getGlobalBounds().width / 2 ,
//			pos.x + body[i].getGlobalBounds().width / 2 };
//		float RecY[4] = { pos.y - body[i].getGlobalBounds().height / 2,
//			pos.y + body[i].getGlobalBounds().height / 2,
//			pos.y + body[i].getGlobalBounds().height / 2 ,
//			pos.y - body[i].getGlobalBounds().height / 2 };
//
//		float x1 = posPlayer.x - 3; //left
//		float x2 = posPlayer.x + 3; //right
//		float y1 = posPlayer.y - 12; //top -3
//		float y2 = posPlayer.y - 1; //bot
//		/*
//		   x1  x2
//		   v   v
//			---   <-y1
//		   |   |
//		   |   |
//			---   <-y2
//
//		*/
//		for (int f = 0; f < 4; f++)
//		{
//			if (RecX[f] >= x1 and RecX[f] <= x2 and RecY[f] <= y2 and RecY[f] >= y1)
//			{
//
//				if (body[i].getTexture() == &texture[0])
//				{
//					score += 1 * scoreBoost;
//					emo = 0;
//				}
//				else if (body[i].getTexture() == &texture[1])
//				{
//					score += 10 * scoreBoost;
//					emo = 0;
//
//				}
//				else if (body[i].getTexture() == &texture[2])
//				{
//					score += 100 * scoreBoost;
//					emo = 0;
//				}
//				else if (body[i].getTexture() == &texture[3])
//				{
//					score += 1000 * scoreBoost;
//					emo = 0;
//				}
//				else if (body[i].getTexture() == &texture[4])
//				{
//					if (health + 1 <= 10) health++;
//					emo = 1;
//				}
//				else if (body[i].getTexture() == &texture[5] )
//				{
//					speed = 100 ;
//					bonusSpeed = true;
//					emo = 3;
//				}
//				else if (body[i].getTexture() == &texture[6])
//				{
//					scoreBoost = 2;
//					startScoreBoost = true;
//					emo = 5;
//				}
//				else if (body[i].getTexture() == &texture[7])
//				{
//					health = 0;
//				}
//				else if (body[i].getTexture() == &texture[8] )
//				{
//					speed = 20;
//					bonusSpeed = true;
//					emo = 4;
//				}
//				Delete.push_back(i);
//				break;
//			}
//
//		}
//	
//	}
//	for (int i = Delete.size() - 1; i >= 0; i--)
//	{
//		body.erase(body.begin() + Delete[i]);
//	}
//}


void Food::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < body.size(); i++)
	{
		window.draw(body[i]);
	}
}

bool Food::CheckTexture(sf::Sprite OneFood, sf::Texture& tex)
{
	return OneFood.getTexture() == &tex;
}





