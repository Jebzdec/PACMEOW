#include "GameOver.h"

GameOver::GameOver(sf::View& view)
{
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	if (!backgroundTexture.loadFromFile("picture/state/gameoverBG.png")) {}
	background.setTexture(backgroundTexture);
	background.setOrigin(sf::Vector2f(background.getGlobalBounds().width / 2, background.getGlobalBounds().height / 2));
	background.setPosition(view.getSize().x / 2, view.getSize().y / 2);

	if (!font.loadFromFile("font/font2.ttf")) {}
	text.setFont(font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Red);
	text.setString("GameOver");
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
}

GameOver::~GameOver()
{
}

void GameOver::Update(sf::View& view)
{
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	text.setPosition(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2.5));
}

void GameOver::Draw(sf::RenderWindow& window, sf::View& view)
{

	window.draw(background);
	window.setView(view);
	//window.draw(text);
	//std::cout << (std::string)text.getString() << std::endl;
}

void GameOver::Event(sf::RenderWindow& window, sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::Enter:
			CurrentState = 5;
			break;
		}
		break;
	}
}

