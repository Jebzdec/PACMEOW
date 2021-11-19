#include "Menu.h"
int state;
Menu::Menu(sf::View& view)
{
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	if (!backgroundTexture.loadFromFile("picture/state/BackgroundMenu.png")) {}
	background.setTexture(backgroundTexture);
	background.setOrigin(sf::Vector2f(background.getGlobalBounds().width / 2, background.getGlobalBounds().height / 2));
	background.setPosition(view.getSize().x / 2, view.getSize().y / 2);
	//std::cout << view.getSize().y / 2 << std::endl;
	//std::cout << background.getGlobalBounds().height << std::endl;
	if (!font.loadFromFile("font/font2.ttf")) {}
	menu[0].setFont(font);
	menu[0].setCharacterSize(60);
	menu[0].setFillColor(sf::Color::Color(44, 52, 107));
	menu[0].setString("Play");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 4);
	menu[0].setPosition(sf::Vector2f(view.getSize().x /2, view.getSize().y * 4 / 10));

	menu[1].setFont(font);
	menu[1].setCharacterSize(36);
	menu[1].setFillColor(sf::Color::Black);
	menu[1].setString("Leaderboard");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 4);
	menu[1].setPosition(sf::Vector2f(view.getSize().x /2, view.getSize().y * 5 / 10));

	menu[2].setFont(font);
	menu[2].setCharacterSize(36);
	menu[2].setFillColor(sf::Color::Black);
	menu[2].setString("How     to     play");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 4);
	menu[2].setPosition(sf::Vector2f(view.getSize().x /2, view.getSize().y * 6 / 10));

	menu[3].setFont(font);
	menu[3].setCharacterSize(36);
	menu[3].setFillColor(sf::Color::Black);
	menu[3].setString("Exit");
	menu[3].setOrigin(menu[3].getLocalBounds().width / 2, menu[3].getLocalBounds().height / 4);
	menu[3].setPosition(sf::Vector2f(view.getSize().x /2, view.getSize().y * 7 / 10));
	//std::cout << width << height << " \n";
}

Menu::~Menu()
{
}



void Menu::Draw(sf::RenderWindow& window, sf::View& view)
{
	window.setView(view);

	window.draw(background);

	//window.setView(view);
	for (int i = 0; i < MAX_ITEMS; i++) {

		menu[i].setOrigin(menu[i].getLocalBounds().width / 2, menu[i].getLocalBounds().height * (i + 3) / 7.5);
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::Black);
		menu[selectedItem].setCharacterSize(36);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Color(44, 52, 107));
		menu[selectedItem].setCharacterSize(60);
	}
}

void Menu::MoveDown()
{
	if (selectedItem + 1 < MAX_ITEMS)
	{
		menu[selectedItem].setFillColor(sf::Color::Black);
		menu[selectedItem].setCharacterSize(36);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Color(44, 52, 107));
		menu[selectedItem].setCharacterSize(60);
	}
}

void Menu::Event(sf::RenderWindow& window, sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::W:
			MoveUp();
			break;
		case sf::Keyboard::S:
			MoveDown();
			break;
		case sf::Keyboard::Up:
			MoveUp();
			break;
		case sf::Keyboard::Down:
			MoveDown();
			break;
		case sf::Keyboard::Enter:
			switch (GetPressedItem())
			{
			case 0:
				CurrentState = 1;//input name -> state 2 = game
				//std::cout << state.currentState();
				break;
			case 1:
				CurrentState = 5;//leader board
				break;
			case 2:
				CurrentState = 6;
				break;
			case 3:
				window.close();
				break;
			}
			break;
		}
		break;
	}
}


