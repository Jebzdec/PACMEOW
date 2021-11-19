#include "GameState.h"

GameState::GameState(sf::View& view) {
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	if (!backgroundTexture.loadFromFile("picture/popup.png")) {}
	background.setTexture(backgroundTexture);

	std::srand(static_cast<unsigned>(time(NULL)));
	if (!map.LoadFromFile("picture/Map1.tmx")) {}
	if (!playerTexture.loadFromFile("picture/neko.png")) {}
	if (!monsterTexture.loadFromFile("picture/monster.png")) {}
	if (!font.loadFromFile("font/font2.ttf")) {}
	this->player = new Player(&playerTexture, sf::Vector2u(3, 4), 0.3f, 60.f);
	this->monster = new Monster(&monsterTexture, sf::Vector2u(3, 4), 10.f, 60.f);
	this->emotion = new Emotion();
	initHeart();
	initScore();
	initMenu();
	this->food = new Food();
	deltaTime = 0.4f;
	pause = false;
	health = 5;
	currentEmotion = -1;
	score = 0;
	checkScore = 0;
	path.clear();

	status.setSize(sf::Vector2f(1350.f, 10.f));
	status.setOrigin(0, 0);
	status.setFillColor(sf::Color::White);

}

GameState::~GameState()
{
}

void GameState::Update(sf::View& view)
{
	deltaTime = clock.restart().asSeconds();

	if (pause == 1) {}
	else if (pause == 2)
	{

		countGameOver.restart().asSeconds();
		pause = 3;
		currentEmotion = 6;
	}
	else if (pause == 3) {
		if (countGameOver.getElapsedTime() >= sf::seconds(3)) {
			CurrentState = 4;
		}
		currentEmotion = 6;
	}
	else
	{
		view.setCenter(this->player->GetPosition());
		UpdatePlayer(deltaTime, false);
		UpdathHeart(view);
		UpdateFood();
		UpdateMonster(deltaTime);
		//this->player->Update(deltaTime, false);
		//this->food->Update();
		//this->monster->Update(deltaTime, false);
	}

	if (currentEmotion != -1)
	{
		UpdateEmotion(currentEmotion);
	}
	sf::Vector2f v = view.getSize();
	status.setPosition(this->player->GetPosition().x - (v.x / 2), this->player->GetPosition().y - (v.y / 2));

}

void GameState::Draw(sf::RenderWindow& window, sf::View& view)
{
	window.setView(view);
	map.Draw(window);
	this->food->Draw(window);
	this->player->Draw(window);
	this->monster->Draw(window);
	DrawScore(window, view);
	DrawHeart(window);
	//window.draw(status);
	if (currentEmotion != -1)
	{
		this->emotion->Draw(window, currentEmotion);
	}
	if (pause == 1)
	{
		background.setScale(0.125, 0.125);
		background.setOrigin(sf::Vector2f(background.getGlobalBounds().width / 2, background.getGlobalBounds().height / 2));
		background.setPosition(this->player->GetPosition().x - 105, this->player->GetPosition().y - 58);
		window.draw(background);
		int w = -20;
		for (int i = 0; i < MAX_ITEMS; i++) {
			menu[i].setPosition(this->player->GetPosition().x, this->player->GetPosition().y + w);
			window.draw(menu[i]);
			w += 20;
		}
	}
}

void GameState::Pause()
{
	pause = !pause;
}

void GameState::initHeart()
{
	heart.resize(MAX_HEART);
	if (!heartTexture.loadFromFile("picture/heart.png")) {}
	for (int i = 0; i < MAX_HEART; i++)
	{
		heart[i].setTexture(heartTexture);
		heart[i].setScale(0.35, 0.35);
	}
}

void GameState::UpdathHeart(sf::View& view)
{
	sf::Vector2f v = view.getSize();
	int w = 10;
	if (health > 0)
	{
		for (int i = 0; i < health; i++)
		{
			heart[i].setPosition(this->player->GetPosition().x - (v.x / 2) + w, this->player->GetPosition().y - (v.y / 2) + 5);
			w += 8;
		}
	}
	else {
		if (pause == 0)
			gameOver();
	}
}

void GameState::DrawHeart(sf::RenderWindow& window)
{
	for (int i = 0; i < health; i++)
	{
		window.draw(heart[i]);
	}
}

void GameState::gameOver()
{
	pause = 2;
	WriteFile();
	//CurrentState = 4;
}

void GameState::Event(sf::RenderWindow& window, sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
		if (!pause)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::P:
				Pause();
				break;
			}
			break;
		}

		else
		{
			switch (event.key.code)
			{
			case sf::Keyboard::P:
				Pause();
				break;
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
					pause = false;//input name -> state 2 = game
					//std::cout << state.currentState();
					break;
				case 1:
					CurrentState = -1;
					break;
				case 2:
					CurrentState = 0;
					break;
				}
				break;
			}
		}
	}
}

void GameState::initScore()
{
	textScore.setFont(font);
	textScore.setCharacterSize(100);
	textScore.setScale(0.1, 0.1);
	textScore.setFillColor(sf::Color::Red);
}

void GameState::DrawScore(sf::RenderWindow& window, sf::View& view)
{
	if (checkScore - score > 10000) {
		checkScore = score;
		this->monster->speed += 0.2;
	}
	sf::Vector2f v = view.getSize();
	textScore.setString(std::to_string(score));
	textScore.setOrigin(textScore.getLocalBounds().width, 0);
	textScore.setPosition(this->player->GetPosition().x + (v.x / 2) - 10, this->player->GetPosition().y - (v.y / 2) + 1);
	window.draw(textScore);
}

void GameState::WriteFile()
{
	std::string read, sName, sScore;
	unsigned int readScore;
	std::fstream file;
	std::priority_queue<std::pair<int, std::string>> q;
	file.open("score.txt");
	if (name.size() == 0)
		name = "Anonymous";
	q.push({ score,name });
	if (file.is_open())
	{
		while (std::getline(file, read))
		{
			int space = read.find(' ');
			sName = read.substr(0, space);
			sScore = read.substr(space + 1, read.size());
			int iScore = stoi(sScore);
			q.push({ iScore,sName });
		}
		file.close();
	}
	std::ofstream file2("score.txt", std::ios::out | std::ios::trunc);
	if (file2.is_open())
	{
		int i = 0;
		while (!q.empty() and i < 5)
		{
			file2 << q.top().second << " " << q.top().first << std::endl;
			//std::cout << q.top().first << " " << q.top().second << std::endl;
			q.pop();
			//std::cout << i << std::endl;
			i++;
		}
		file2.close();
	}
}

void GameState::initMenu()
{

	menu[0].setFont(font);
	menu[0].setCharacterSize(50);
	menu[0].setScale(0.1, 0.1);
	menu[0].setFillColor(sf::Color::Color(225, 241, 107));
	menu[0].setString("Resume");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);

	menu[1].setFont(font);
	menu[1].setCharacterSize(50);
	menu[1].setScale(0.1, 0.1);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Restart");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);

	menu[2].setFont(font);
	menu[2].setCharacterSize(50);
	menu[2].setScale(0.1, 0.1);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Back     to     menu");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);
}

void GameState::MoveDown()
{
	if (selectedItem + 1 < MAX_ITEMS)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Color(225, 241, 107));
	}
}

void GameState::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Color(225, 241, 107));
	}
}

void GameState::UpdatePlayer(float deltaTime, bool press)
{
	if (this->player->speed != 60)
	{
		if (this->player->bonusSpeed == true)
		{
			countTimeSpeed.restart().asSeconds();
			this->player->bonusSpeed = false;
		}
		if (countTimeSpeed.getElapsedTime() >= sf::seconds(10))
		{
			this->player->speed = 60;
		}

	}

	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		movement.x -= this->player->speed * deltaTime;
		press = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		movement.x += this->player->speed * deltaTime;
		press = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		movement.y -= this->player->speed * deltaTime;
		press = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		movement.y += this->player->speed * deltaTime;
		press = true;
	}
	if (movement.y > 0.0f) {
		this->player->row = 0;
	}
	else if (movement.y < 0.0f) {
		this->player->row = 3;
	}

	if (movement.x < 0.0f) {
		this->player->row = 1;
	}
	else if (movement.x > 0.0f) {
		this->player->row = 2;
	}

	if (press)
	{
		this->player->animation.Update(this->player->row, deltaTime);
	}
	sf::Vector2f p = this->player->body.getPosition() + movement;
	int X = (p.x - 0.5) / 16;
	int Y = (p.y - 2) / 16;
	if (!solid[Y][X]) {
		this->player->body.setTextureRect(this->player->animation.uvRect);
		this->player->body.move(movement);
	}
}

void GameState::UpdateMonster(float deltaTime)
{
	for (int qd = 0; qd < 5; qd++)
	{
		for (int i = 0; i < this->monster->body[qd].size(); i++)
		{
			sf::Vector2f movement(0.0f, 0.0f);

			movement.x = this->monster->speed * deltaTime * this->monster->direction[this->monster->RandDir[qd][i]][0];
			movement.y = this->monster->speed * deltaTime * this->monster->direction[this->monster->RandDir[qd][i]][1];

			if (movement.y > 0.0f)
			{
				this->monster->row[qd][i] = 0;
			}
			else if (movement.y < 0.0f)
			{
				this->monster->row[qd][i] = 3;
			}
			if (movement.x < 0.0f)
			{
				this->monster->row[qd][i] = 1;
			}
			else if (movement.x > 0.0f)
			{
				this->monster->row[qd][i] = 2;
			}

			sf::Vector2f p = this->monster->body[qd][i].getPosition() + movement;
			int X = (p.x - 0.5) / 16;
			int Y = (p.y - 0.5) / 16;
			//int countW[10] = { 500,1000,2000,3000,4000,5000,6000,7000,8000,9000};
			//int r = rand() % 10;
			//std::cout << r << std::endl;
			if (pathMon[qd][Y][X] and this->monster->countWalk[qd][i] < this->monster->MaxWalk[qd][i] and X >= 0 and Y >= 0 and X < 32 and Y < 32)
			{
				this->monster->animation.Update(this->monster->row[qd][i], deltaTime);
				this->monster->body[qd][i].setTextureRect(this->monster->animation.uvRect);
				this->monster->body[qd][i].move(movement);
				this->monster->countWalk[qd][i]++;
			}
			else
			{
				this->monster->RandDir[qd][i] = rand() % 4;
				this->monster->countWalk[qd][i] = 0; 
				int countW[12] = { 500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,11000 };
				this->monster->MaxWalk[qd][i] = countW[rand()%12];
			}

			sf::Vector2f pAf = this->monster->body[qd][i].getPosition();
			float x1 = pAf.x - 3.8;
			float x2 = pAf.x + 3.8;
			float y1 = pAf.y - 6.5;
			float y2 = pAf.y + 7;
			/*
			   x1  x2
			   v   v
				---   <-y1
			   |   |
			   |   |
				---   <-y2

			*/
			if (countTimeMonster.getElapsedTime() >= sf::seconds(0.5))
			{
				startCountTimeMonster = false;
			}
			sf::Vector2f posPlayer = this->player->body.getPosition();
			float RecX[4] = { posPlayer.x - 3, posPlayer.x + 3, posPlayer.x - 3, posPlayer.x + 3 };
			float RecY[4] = { posPlayer.y - 11 , posPlayer.y, posPlayer.y , posPlayer.y - 11 };
			for (int p = 0; p < 4; p++)
			{
				if (RecX[p] >= x1 and RecX[p] <= x2 and RecY[p] <= y2 and RecY[p] >= y1 and !startCountTimeMonster)
				{
					//std::cout << health << std::endl;
					startCountTimeMonster = true;
					countTimeMonster.restart().asSeconds();
					health--;
					currentEmotion = 2;
					break;
				}
			}
		}
	}
}

void GameState::UpdateFood()
{
	std::vector<int> Delete;
	if (this->food->body.size()<=30)
	{
		NextLevel();
	}
	if (scoreBoost == 2) {
		if (startScoreBoost == true)
		{
			countTimeSpeed.restart().asSeconds();
			startScoreBoost = false;
		}
		if (countTimeSpeed.getElapsedTime() >= sf::seconds(10))
		{
			scoreBoost = 1;
		}
	}
	for (int i = 0; i < this->food->body.size(); i++)
	{
		sf::Vector2f pos = this->food->body[i].getPosition();
		float RecX[4] = { pos.x - this->food->body[i].getGlobalBounds().width / 2 ,
			pos.x + this->food->body[i].getGlobalBounds().width / 2 ,
			pos.x - this->food->body[i].getGlobalBounds().width / 2 ,
			pos.x + this->food->body[i].getGlobalBounds().width / 2 };
		float RecY[4] = { pos.y - this->food->body[i].getGlobalBounds().height / 2,
			pos.y + this->food->body[i].getGlobalBounds().height / 2,
			pos.y + this->food->body[i].getGlobalBounds().height / 2 ,
			pos.y - this->food->body[i].getGlobalBounds().height / 2 };

		sf::Vector2f posPlayer = this->player->body.getPosition();
		float x1 = posPlayer.x - 3.5; //left
		float x2 = posPlayer.x + 3.5; //right
		float y1 = posPlayer.y - 13; //top -3
		float y2 = posPlayer.y - 1; //bot
		/*
		   x1  x2
		   v   v
			---   <-y1
		   |   |
		   |   |
			---   <-y2

		*/
		for (int f = 0; f < 4; f++)
		{
			if (RecX[f] >= x1 and RecX[f] <= x2 and RecY[f] <= y2 and RecY[f] >= y1)
			{

				if (this->food->CheckTexture(this->food->body[i], this->food->texture[0]))
				{
					score += 1 * scoreBoost;
					currentEmotion = 0;
				}
				else if (this->food->CheckTexture(this->food->body[i], this->food->texture[1]))
				{
					score += 10 * scoreBoost;
					currentEmotion = 0;

				}
				else if (this->food->CheckTexture(this->food->body[i], this->food->texture[2]))
				{
					score += 100 * scoreBoost;
					currentEmotion = 0;
				}
				else if (this->food->CheckTexture(this->food->body[i], this->food->texture[3]))
				{
					score += 1000 * scoreBoost;
					currentEmotion = 0;
				}
				else if (this->food->CheckTexture(this->food->body[i], this->food->texture[4]))
				{
					if (health + 1 <= 10) health++;
					currentEmotion = 1;
				}
				else if (this->food->CheckTexture(this->food->body[i], this->food->texture[5]))
				{
					this->player->speed = 100;
					this->player->bonusSpeed = true;
					currentEmotion = 3;
				}
				else if (this->food->CheckTexture(this->food->body[i], this->food->texture[6]))
				{
					scoreBoost = 2;
					startScoreBoost = true;
					currentEmotion = 5;
				}
				else if (this->food->CheckTexture(this->food->body[i], this->food->texture[7]))
				{
					health = 0;
				}
				else if (this->food->CheckTexture(this->food->body[i], this->food->texture[8]))
				{
					this->player->speed = 20;
					this->player->bonusSpeed = true;
					currentEmotion = 4;
				}
				Delete.push_back(i);
				break;
			}

		}

	}
	for (int i = Delete.size() - 1; i >= 0; i--)
	{
		this->food->body.erase(this->food->body.begin() + Delete[i]);
	}
}

void GameState::UpdateEmotion(int curEmo)
{
	this->emotion->animation->Update(this->emotion->row[curEmo], deltaTime);
	this->emotion->emotion[curEmo].setTextureRect(this->emotion->animation->uvRect);
	this->emotion->emotion[curEmo].setPosition(this->player->GetPosition().x - 5, this->player->GetPosition().y - 25);
}

void GameState::NextLevel()
{
	//this->monster = new Monster(&monsterTexture, sf::Vector2u(3, 4), 10.f, 70.f);
	//path.clear();
	this->monster->speed += 10;
	this->food = new Food();
}

