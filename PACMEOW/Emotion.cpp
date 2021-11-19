#include "Emotion.h"

Emotion::Emotion()
{
	emotionTexture[0].loadFromFile("picture/emotion/eaten.png");
	emotionTexture[1].loadFromFile("picture/emotion/heartevent.png");
	emotionTexture[2].loadFromFile("picture/emotion/ghostevent.png");
	emotionTexture[3].loadFromFile("picture/emotion/speedup.png");
	emotionTexture[4].loadFromFile("picture/emotion/speeddown.png");
	emotionTexture[5].loadFromFile("picture/emotion/scoreevent.png");
	emotionTexture[6].loadFromFile("picture/emotion/gameover.png");
	for (int i = 0; i < 7; i++)
	{
		this->animation = new Animation(&emotionTexture[i], sf::Vector2u(3, 1), 0.2f);
		emotion[i].setSize(sf::Vector2f(10, 10));
		emotion[i].setTexture(&emotionTexture[i]);
		row[i] = 0;
	}
}

Emotion::~Emotion()
{
}

//void Emotion::Update(float deltaTime,int i,int x,int y)
//{
//	this->animation->Update(row[i], deltaTime);
//	emotion[i].setTextureRect(animation->uvRect);
//	emotion[i].setPosition(x - 5, y - 25);
//}

void Emotion::Draw(sf::RenderWindow& window, int i)
{
	window.draw(emotion[i]);
}
