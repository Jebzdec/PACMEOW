#include "Game.h"
Game::Game()
{
    window.create(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGH), "PACMEOW");//,,sf::Style::Fullscreen 
    view1.setCenter(sf::Vector2f(0.0f, 0.0f));
    view1.setSize(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGH));

    view2.setCenter(sf::Vector2f(0.0f, 0.0f));
    view2.setSize(sf::Vector2f(VIEW_WIDTH / 8, VIEW_HEIGH / 8));
    //NewGame();

    if (!music.openFromFile("bgm/BGM Cute_Play with me!.wav")) {}

    music.play();
    music.setLoop(true);
    //NewGame();
    this->gameOver = new GameOver(view1);
    this->howToPlay = new HowToPlay(view1);
    this->leaderboard = new Leaderboard(view1);
    this->menu = new Menu(view1);
}

Game::~Game()
{
}
void Game::NewGame()
{
    lose = 0;
    this->inputNameState = new InputNameState(view1);
    this->gameState = new GameState(view2);
    deltaTime = 0.0f;
    name = "";

    //for (int i = 0; i < 4; i++) {
    //    for (int j = 0; j < 32; j++) {
    //        for (int k = 0; k < 32; k++) {
    //            std::cout << pathMon[i][j][k];
    //        }std::cout << "\n";
    //    }std::cout << "\n";
    //}
}
void Game::RestartGame()
{
    lose = 0;
    this->gameState = new GameState(view2);
    deltaTime = 0.0f;
}
void Game::RunGame()
{
    while (window.isOpen())
    {

        //std::cout << window.getSize().x << " " << float(window.getSize().y) << std::endl;
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (CurrentState)
            {
            case 0:
                this->menu->Event(window, event);
                //cout << state.currentState();
                break;
            case 2:
                this->inputNameState->Event(window, event);
                break;
            case 3:
                if (this->gameState->pause <= 1)
                {
                    this->gameState->Event(window, event);
                }
                if (CurrentState == -1)
                {
                    RestartGame();
                    CurrentState = 3;
                }
                break;
            case 4:
                this->gameOver->Event(window, event);
                break;
            case 5:
                this->leaderboard->Event(window, event);
                break;
            case 6:
                this->howToPlay->Event(window, event);
                break;
            }
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view1, 1);
                ResizeView(window, view2, 8);
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                }
                break;
            }
        }

        UpdateGame();
        RenderGame();
    }
}

void Game::UpdateGame()
{
    switch (CurrentState)
    {
    case 0:
        break;
    case 1:
        NewGame();
        CurrentState = 2;
        break;
    case 2:
        this->inputNameState->Update(view1);
        break;
    case 3:
        this->gameState->Update(view2);
        break;
    case 4:
        this->gameOver->Update(view1, this->gameState->score);
        break;
    case 5:
        this->leaderboard->Update(view1);
        break;
    }
}

void Game::RenderGame()
{
    window.clear();
    switch (CurrentState)
    {
    case 0:
        //view1.setCenter(VIEW_WIDTH / 2, VIEW_HEIGH / 2);
        this->menu->Draw(window, view1);
        break;
    case 1:
        break;
    case 2:
        //view1.setCenter(VIEW_WIDTH / 2, VIEW_HEIGH / 2);
        this->inputNameState->Draw(window, view1);
        break;
    case 3:
        this->gameState->Draw(window, view2);
        break;
    case 4:
        if (lose == 0)
        {
            this->gameOver->effLose.play();
            lose = 1;
        }
        //view1.setCenter(VIEW_WIDTH / 2, VIEW_HEIGH / 2);
        this->gameOver->Draw(window, view1);
        break;
    case 5:
        this->leaderboard->Draw(window, view1);
        break;
    case 6:
        this->howToPlay->Draw(window, view1);
        break;
    }
    //std::cout << CurrentState << std::endl;
    window.display();
}

void Game::ResizeView(const sf::RenderWindow& window, sf::View& view, int zoom)
{
    //std::cout << window.getSize().x << " " << float(window.getSize().y) <<std::endl;
    //std::cout << view.getSize().x << " " << view.getSize().y << std::endl;
    double aspectRatio = float(window.getSize().x / float(window.getSize().y));
    view.setSize(VIEW_WIDTH / zoom, VIEW_HEIGH / zoom);

    //std::cout << view.getSize().x << " " << view.getSize().y << std::endl;
}

