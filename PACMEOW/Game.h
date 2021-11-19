#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "State.h"
#include "GameState.h"
#include "Menu.h"
#include "InputNameState.h"
#include "GameOver.h"
#include "Leaderboard.h"
#include "HowToPlay.h"

using namespace tinyxml2;
using namespace std;

class Game
{
private:
	GameState* gameState;
	Menu* menu;
	InputNameState* inputNameState;
	GameOver* gameOver;
	Leaderboard* leaderboard;
	HowToPlay* howToPlay;
	sf::RenderWindow window;
	sf::View view1;
	sf::View view2;
	float VIEW_HEIGH = 1080;
	float VIEW_WIDTH = 1920;
	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Music music;
public:
	Game();
	~Game();
	void NewGame();
	void RestartGame();
	void RunGame();
	void UpdateGame();
	void RenderGame();
	void ResizeView(const sf::RenderWindow& window, sf::View& view, int zoom);
};

