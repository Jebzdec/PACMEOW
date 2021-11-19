#include "HowToPlay.h"

HowToPlay::HowToPlay(sf::View& view)
{
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	if (!backgroundTexture.loadFromFile("picture/state/Howtoplay.png")) {}
	background.setTexture(backgroundTexture);
	background.setOrigin(sf::Vector2f(background.getGlobalBounds().width / 2, background.getGlobalBounds().height / 2));
	background.setPosition(view.getSize().x / 2, view.getSize().y / 2);
}

HowToPlay::~HowToPlay()
{
}

void HowToPlay::Draw(sf::RenderWindow& window, sf::View& view)
{
	window.setView(view);
	window.draw(background);
}

void HowToPlay::Event(sf::RenderWindow& window, sf::Event event)
{

	switch (event.type)
	{
	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::Enter:
			CurrentState = 0;
			break;
		}
		break;
	}
}
