#pragma once
#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tinyxml2.h"
extern bool solid[32][32];//tile block
extern bool pathMon[5][32][32];
extern std::vector<std::pair<int, int>> path; //for random path food
extern std::vector<std::pair<int, int>> mon[5]; //for random mon 
struct Object
{
	int GetPropertyInt(std::string name);
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);
	std::string name;
	std::string type;
	sf::Rect<float> rect;
	std::map<std::string, std::string> properties;
	sf::Sprite sprite;
};
struct Layer
{
	int opacity;
	std::vector<sf::Sprite> tiles;
};

class Level
{
public:
	bool LoadFromFile(std::string filename);
	Object GetObject(std::string name);
	std::vector<Object> GetObjects(std::string name);
	std::vector<Object> GetAllObjects();
	void Draw(sf::RenderWindow& window);
	sf::Vector2i GetTileSize();

private:
	int width, height, tileWidth, tileHeight;
	int firstTileID;
	sf::Rect<float> drawingBounds;
	sf::Texture tilesetImage;
	std::vector<Object> objects;
	std::vector<Layer> layers;
};

#endif