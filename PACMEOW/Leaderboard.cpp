#include "Leaderboard.h"
#include "Leaderboard.h"

Leaderboard::Leaderboard(sf::View& view)
{
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	if (!backgroundTexture.loadFromFile("picture/state/leaderboardBG.png")) {}
	background.setTexture(backgroundTexture);
	background.setOrigin(sf::Vector2f(background.getGlobalBounds().width / 2, background.getGlobalBounds().height / 2));
	background.setPosition(view.getSize().x / 2, view.getSize().y / 2);

	if (!font.loadFromFile("font/font2.ttf")) {}
	text.setFont(font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Red);
	text.setString("Leaderboard");
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
}

Leaderboard::~Leaderboard()
{

}

void Leaderboard::Update(sf::View& view)
{

	std::string read, sName, sScore;
	unsigned int readScore;
	std::fstream file;
	file.open("score.txt");
	if (file.is_open())
	{
		int i = 0;
		while (std::getline(file, read))
		{
			int space = read.find(' ');
			rankName[i].setString(read.substr(0, space));
			rankName[i].setFont(font);
			rankName[i].setCharacterSize(100);
			rankName[i].setScale(0.4, 0.4);
			rankName[i].setFillColor(sf::Color::Black);

			rankScore[i].setString(read.substr(space + 1, read.size()));
			rankScore[i].setFont(font);
			rankScore[i].setCharacterSize(100);
			rankScore[i].setScale(0.4, 0.4);
			rankScore[i].setOrigin(rankScore[i].getLocalBounds().width, 0);
			rankScore[i].setFillColor(sf::Color::Black);
			i++;
		}
		file.close();
	}

	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	text.setPosition(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2.5));
	for (int i = 0; i < 5; i++) {
		rankName[i].setPosition(sf::Vector2f(view.getSize().x * 1.2 / 8, view.getSize().y * (i + 2) / 7.8));
		rankScore[i].setPosition(sf::Vector2f(view.getSize().x * 6.6 / 8, view.getSize().y * (i + 2) / 7.8));
	}
}

void Leaderboard::Draw(sf::RenderWindow& window, sf::View& view)
{
	window.draw(background);
	for (int i = 0; i < 5; i++) {
		window.draw(rankName[i]);
		window.draw(rankScore[i]);
	}
	window.setView(view);
	//window.draw(text);
}

void Leaderboard::Event(sf::RenderWindow& window, sf::Event event)
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
