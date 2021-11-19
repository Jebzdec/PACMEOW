#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include "State.h"

extern std::string name;
class InputNameState
{
public:
	InputNameState(sf::View& view);
	~InputNameState();
	void Add(char c);
	void Delete();
	void Update(sf::View& view);
	void Draw(sf::RenderWindow& window, sf::View& view);
	void Event(sf::RenderWindow& window, sf::Event event);
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::Text text;
	sf::Font font;
};

