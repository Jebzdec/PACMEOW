#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "Map.h"
#include "Player.h"
#include "tinyxml2.h"
#include "Monster.h"
#include <time.h>
#include "food.h"
#include "State.h"
#include "InputNameState.h"
#include "Emotion.h"

#define MAX_ITEMS 3
#define MAX_HEART 16
class GameState
{
public:
	GameState(sf::View& view);
	~GameState();
	void Update(sf::View& view);
	void Draw(sf::RenderWindow& window, sf::View& view);
	void Pause();
	void initHeart();
	void UpdathHeart(sf::View& view);
	void DrawHeart(sf::RenderWindow& window);

	void gameOver();

	void Event(sf::RenderWindow& window, sf::Event event);

	void initScore();
	void DrawScore(sf::RenderWindow& window, sf::View& view);


	void WriteFile();

	void initMenu();
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItem; }

	void UpdatePlayer(float deltaTime, bool press);
	void UpdateMonster(float deltaTime);
	void UpdateFood();
	void UpdateEmotion(int curEmo);

	void NextLevel();
	int pause = false;
private:
	sf::Texture playerTexture;
	sf::Texture monsterTexture;

	sf::Clock clock;
	sf::Clock countGameOver;
	float deltaTime = 0.0f;
	Level map;
	Food* food;
	Player* player;
	Monster* monster;
	Emotion* emotion;
	sf::RectangleShape status;
	sf::Texture heartTexture;
	std::vector<sf::Sprite> heart{ MAX_HEART };
	sf::Text textScore;
	sf::Font font;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	char writeName[20];
	unsigned long writeScore;
	unsigned long score, checkScore;


	int row;
	sf::Text menu[MAX_ITEMS];
	int selectedItem = 0;

	sf::Clock countTimeMonster;
	bool startCountTimeMonster;
	sf::Clock countTimeSpeed;
	bool startScoreBoost;
	int countFood[9] = {};
	int scoreBoost = 1;
	int health;
	int currentEmotion;

};

