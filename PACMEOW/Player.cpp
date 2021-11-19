#pragma once
#include "Player.h"
#define bodyWidth 16
#define bodyHigh 16/*
sf::Vector2f posPlayer;
int health;
float speed;
bool bonusSpeed;
int emo;*/
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float Speed) :
	animation(texture, imageCount, switchTime)
{
	speed = Speed;
	row = 0;
	bonusSpeed = false;

	body.setSize(sf::Vector2f(bodyWidth, bodyHigh));
	body.setOrigin(bodyWidth / 2, bodyHigh);
	body.setPosition(250.5, 315.5);//.5 center of block i j
	body.setTexture(texture);
}

Player::~Player()
{
}


//void Player::Update(float deltaTime, bool press)
//{
//
//	if (speed != 60)
//	{
//		if (bonusSpeed == true)
//		{
//			countTimeSpeed.restart().asSeconds();
//			bonusSpeed = false;
//		}
//		if (countTimeSpeed.getElapsedTime() >= sf::seconds(10))
//		{
//			speed = 60;
//		}
//
//	}
//
//	sf::Vector2f movement(0.0f, 0.0f);
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//	{
//		movement.x -= speed * deltaTime;
//		//dirX = -1;
//		//dirY = 0;
//		press = true;
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//	{
//		movement.x += speed * deltaTime;
//		//dirX = 1;
//		//dirY = 0;
//		press = true;
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//	{
//		movement.y -= speed * deltaTime;
//		//dirY = -1;
//		//dirX = 0;
//		press = true;
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//	{
//		movement.y += speed * deltaTime;
//		//dirY = 1;
//		//dirX = 0;
//		press = true;
//	}
//	if (movement.y > 0.0f) {
//		row = 0;
//	}
//	else if (movement.y < 0.0f) {
//		row = 3;
//	}
//
//	if (movement.x < 0.0f) {
//		row = 1;
//	}
//	else if (movement.x > 0.0f) {
//		row = 2;
//	}
//
//
//	if (press)
//	{
//		animation.Update(row, deltaTime);
//	}
//	sf::Vector2f p = body.getPosition() + movement;
//	int X = (p.x - 0.5) / 16;
//	int Y = (p.y - 2) / 16;
//	if (!solid[Y][X]) {
//		body.setTextureRect(animation.uvRect);
//		body.move(movement);
//		posPlayer = body.getPosition();
//	}
//	//std::cout << X << Y << "\n";
//}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}


