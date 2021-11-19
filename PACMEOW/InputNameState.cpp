#include "InputNameState.h"


std::string name;
InputNameState::InputNameState(sf::View& view)
{
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	if (!backgroundTexture.loadFromFile("picture/state/inputname.png")) {}
	background.setTexture(backgroundTexture);
	background.setOrigin(sf::Vector2f(background.getGlobalBounds().width / 2, background.getGlobalBounds().height / 2));
	background.setPosition(view.getSize().x / 2, view.getSize().y / 2);

	if (!font.loadFromFile("font/font2.ttf")) {}
	text.setFont(font);
	text.setCharacterSize(52);
	text.setFillColor(sf::Color::Black);
}

InputNameState::~InputNameState()
{
}

void InputNameState::Add(char c)
{
	name += c;
}

void InputNameState::Delete()
{
	if (name.size() > 0)
	{
		name.erase(name.end() - 1);
	}

}

void InputNameState::Update(sf::View& view)
{
	text.setString(name);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(view.getSize().x / 2, view.getSize().y / 2);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
}

void InputNameState::Draw(sf::RenderWindow& window, sf::View& view)
{
	window.setView(view);
	window.draw(background);
	window.draw(text);
}

void InputNameState::Event(sf::RenderWindow& window, sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::Backspace:
			Delete();
			break;
		case sf::Keyboard::Enter:
			CurrentState = 3;
			break;
		}
		break;
	case sf::Event::TextEntered:
		if (isalnum(event.text.unicode) and name.size() < 20)
		{
			Add(char(event.text.unicode));
		}
		break;
	}
}
