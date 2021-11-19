#pragma once
#include "Monster.h"

#define bodyWidth 16
#define bodyHigh 16
//int direction[8][2] = { {-1,-1 },{-1,0},{-1,1}, {0,-1},{0,1},{1,-1},{1,0}, {1,1} };
Monster::Monster(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	int direction[4][2] = { {-1,0}, {0,-1},{0,1},{1,0} };
	for (int quadrant = 0; quadrant < 5; quadrant++)
	{
		body[quadrant].resize(MonsterNumber);
		for (int i = 0; i < MonsterNumber; i++)
		{
			this->speed = speed;
			countWalk[quadrant][i] = 0;
			row[quadrant][i] = 0;
			body[quadrant][i].setSize(sf::Vector2f(bodyWidth, bodyHigh));
			body[quadrant][i].setOrigin(bodyWidth / 2, bodyHigh / 2);
			int Rand = rand() % mon[quadrant].size();
			RandDir[quadrant][i] = rand() % 4;
			//std::cout << path[Rand].first << " " << path[Rand].second << " " << std::endl;
			body[quadrant][i].setPosition(mon[quadrant][Rand].first * 16 + 10, mon[quadrant][Rand].second * 16 + 10);
			body[quadrant][i].setTexture(texture);
			int countW[12] = { 500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,11000};
			int r = rand() % 12;
			MaxWalk[quadrant][i] = countW[r];
			//std::cout << i << " " << countW[r] << std::endl;
		}
	}

}

Monster::~Monster()
{
}

//void Monster::Update(float deltaTime, bool press)
//{
//	//std::cout << posPlayer.x << " " << posPlayer.y<<std::endl;
//	std::vector<int> Delete;
//	for (int i = 0; i < body.size(); i++)
//	{
//		sf::Vector2f movement(0.0f, 0.0f);
//
//		movement.x = speed * deltaTime * direction[RandDir[i]][0];
//		movement.y = speed * deltaTime * direction[RandDir[i]][1];
//
//		if (movement.y > 0.0f) {
//			row[i] = 0;
//		}
//		else if (movement.y < 0.0f) {
//			row[i] = 3;
//		}
//
//		if (movement.x < 0.0f) {
//			row[i] = 1;
//		}
//		else if (movement.x > 0.0f) {
//			row[i] = 2;
//		}
//		sf::Vector2f p = body[i].getPosition() + movement;
//		int X = (p.x - 0.5) / 16;
//		int Y = (p.y - 0.5) / 16;
//		int countW[7] = { 4000,6000,8000,10000,12000,14000,16000};
//		int r = rand() % 7;
//		if (!solid[Y][X] and countWalk[i]<countW[r] and X>=0 and Y>=0 and X<32 and Y<32) {
//			//std::cout << Y<< " "<<X<<" "<< direction[RandDir[i]][0] << " " << direction[RandDir[i]][1] << " " << "\n";
//			animation.Update(row[i], deltaTime);
//			body[i].setTextureRect(animation.uvRect);
//			body[i].move(movement);
//			countWalk[i]++;
//		}
//		else {
//			RandDir[i] = rand() % 4;
//			countWalk[i] = 0;
//		}
//		sf::Vector2f pAf = body[i].getPosition();
//		int x1 = pAf.x -4;
//		int x2 = pAf.x + 4;
//		int y1 = pAf.y-7;
//		int y2 = pAf.y+7;
//		/*
//		   x1  x2
//		   v   v
//			---   <-y1
//		   |   |
//		   |   |
//			---   <-y2
//			
//		*/
//		int RecX[4] = {posPlayer.x -3, posPlayer.x + 3, posPlayer.x - 3, posPlayer.x +3 };
//		int RecY[4] = {posPlayer.y-11 , posPlayer.y, posPlayer.y , posPlayer.y-11  };
//		for (int p = 0; p < 4; p++) {
//			if(RecX[p]>=x1 and RecX[p]<=x2 and RecY[p]<=y2 and RecY[p]>=y1){
//				health--;
//				Delete.push_back(i);
//				emo = 2;
//				break;
//			}
//			
//		}
//			
//	}
//	
//	for (int i = Delete.size() - 1; i >= 0; i--)
//	{
//		body.erase(body.begin() + Delete[i]);
//	}
//}


void Monster::Draw(sf::RenderWindow& window)
{
	for (int qd = 0; qd < 5; qd++)
	{
		for (int i = 0; i < body[qd].size(); i++)
		{
			window.draw(body[qd][i]);
		}
	}
}