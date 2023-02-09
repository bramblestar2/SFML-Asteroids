#include "Window.h"
#include <time.h>'
#include <iostream>
#include <SFML/Audio.hpp>

Window::Window()
{
	srand(time(NULL));

	initWindow();

	addPlayer(window->getSize().x / 2, window->getSize().y / 2);

	m_asteroid_spawn_rate = 2.5;

	m_player_score = 0;

	if (!shader.loadFromFile("test.vert", "test.frag"))
		std::cout << "FAILED";

	FontHandler::loadFont("GameFont", "KarmaFuture.ttf");
	
	m_score_count.setFillColor(sf::Color::White);
	m_score_count.setFont(*FontHandler::getFont("GameFont"));
	m_score_count.setCharacterSize(35);

	m_player_hit_buffer.loadFromFile("hit.wav");
	m_player_hit.setBuffer(m_player_hit_buffer);

	m_explosion_buffer.loadFromFile("explosion.wav");
	m_explosion.setBuffer(m_explosion_buffer);
	m_explosion.setVolume(30);
	

	//Start menu
	startMenu = new StartMenu(sf::Vector2f(window->getSize()));

	std::function<void()> onClose = [this]() { window->close(); };
	std::function<void()> onStart = [this]() { gameState = GameStates::GAMEPLAY; };
	std::function<void()> onRestart = [this]() { gameState = GameStates::START_MENU; m_player_score = 0; };

	startMenu->setOnClose(onClose);
	startMenu->setOnStart(onStart);

	gameState = GameStates::START_MENU;

	//Pause Menu
	pauseMenu = new PauseMenu(sf::Vector2f(window->getSize()));

	pauseMenu->setOnClose(onClose);
	pauseMenu->setOnRestart(onRestart);
	pauseMenu->setOnUnpause(onStart);

	//Game over menu
	gameOver = new GameOver(sf::Vector2f(window->getSize()));

	gameOver->setOnClose(onClose);
	gameOver->setOnRestart(onRestart);
}

Window::~Window()
{
	while (gameObjects.size() > 0)
		deleteObject(0);

	delete window;

	delete startMenu;
	delete pauseMenu;
	delete gameOver;
}

void Window::run()
{
	while (window->isOpen())
	{
		update();
		updateDt();
		updateSFMLEvents();
		render();
	}
}

void Window::render()
{
	window->clear();

	sf::RenderStates states = sf::RenderStates::Default;

	sf::RenderTexture textureDraw;
	textureDraw.create(window->getSize().x, window->getSize().y);

	/* Render Start Menu */
	if (gameState == GameStates::START_MENU)
	{
		startMenu->draw(textureDraw, states);
	}

	/* Render Gameplay */
	else if (gameState == GameStates::GAMEPLAY || gameState == GameStates::PAUSED)
	{
		textureDraw.draw(m_score_count);

		for (int i = 0; i < gameObjects.size(); i++)
			gameObjects.at(i)->draw(textureDraw, states);

		/* Render pause screen over gameplay*/
		if (gameState == GameStates::PAUSED)
		{
			pauseMenu->draw(textureDraw, states);
		}
	}

	/* Render Gameover */
	else if (gameState == GameStates::GAMEOVER)
	{
		gameOver->draw(textureDraw, states);
	}

	//Render to screen
	sf::Sprite spriteDraw(textureDraw.getTexture());
	sf::Vector2f size(textureDraw.getSize());
	spriteDraw.setTextureRect(sf::IntRect(0, size.y, size.x, -size.y));
	
	//Set shader
	//states.shader = &shader;
	//shader.setUniform("u_ship_coords", gameObjects.at(m_player_index)->getPosition());
	//shader.setUniform("pixelSize", sf::Vector2f(10, 10));
	//shader.setUniform("windowSize", sf::Vector2f(window->getSize()));

	window->draw(spriteDraw, states);
	
	window->display();
}

void Window::update()
{
	if (window->hasFocus())
	{
		if (gameState == GameStates::START_MENU)
		{
			startMenuLogic();
		}

		if (gameState == GameStates::GAMEPLAY)
		{
			gameplayLogic();
		}

		if (gameState == GameStates::GAMEOVER)
		{
			gameoverLogic();
		}
	}
}

void Window::updateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Window::updateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		if (gameState == GameStates::START_MENU)
		{
			startMenu->updateEvents(event);
		}
		else if (gameState == GameStates::PAUSED)
		{
			pauseMenu->updateEvents(event);
		}
		else if (gameState == GameStates::GAMEOVER)
		{
			gameOver->updateEvents(event);
		}

		for (int i = 0; i < gameObjects.size(); i++)
			gameObjects.at(i)->updateEvents(event);

		switch (event.type)
		{
		case sf::Event::Closed:
				window->close();
				break;
		case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					if (gameState == GameStates::GAMEPLAY || gameState == GameStates::PAUSED)
					{
						if (gameState == GameStates::PAUSED)
						{
							gameState = GameStates::GAMEPLAY;
						}
						else
						{
							gameState = GameStates::PAUSED;
						}
					}
				//		window->close();
					break;

				case sf::Keyboard::Q:
					randomAsteroid();
					break;
				}
				break;
		}
	}
}

void Window::initWindow()
{
	sf::VideoMode vidMode = sf::VideoMode::getDesktopMode();
	
	window = new sf::RenderWindow(sf::VideoMode(400, 300, vidMode.bitsPerPixel),
									"Asteroids", sf::Style::Default);
	window->setFramerateLimit(60);
}

void Window::offScreen()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (offTop(*gameObjects.at(i)))
		{
			gameObjects.at(i)->setPosition(gameObjects.at(i)->getPosition().x, 
						window->getSize().y + gameObjects.at(i)->getRadius());
		}
		else if (offBottom(*gameObjects.at(i)))
		{
			gameObjects.at(i)->setPosition(gameObjects.at(i)->getPosition().x, 
											-gameObjects.at(i)->getRadius());
		}

		if (offLeft(*gameObjects.at(i)))
		{
			gameObjects.at(i)->setPosition(window->getSize().x + 
				gameObjects.at(i)->getRadius(), gameObjects.at(i)->getPosition().y);
		}
		else if (offRight(*gameObjects.at(i)))
		{
			gameObjects.at(i)->setPosition(-gameObjects.at(i)->getRadius(), 
										gameObjects.at(i)->getPosition().y);
		}
	}
}

bool Window::offTop(const GameObject& object)
{
	return object.getPosition().y < -object.getRadius();
}

bool Window::offBottom(const GameObject& object)
{
	return object.getPosition().y > window->getSize().y + object.getRadius();
}

bool Window::offLeft(const GameObject& object)
{
	return object.getPosition().x < -object.getRadius();
}

bool Window::offRight(const GameObject& object)
{
	return object.getPosition().x > window->getSize().x + object.getRadius();
}

void Window::deleteObject(const int index)
{
	if (index >= 0 && index < gameObjects.size())
	{
		if (gameObjects.at(index)->getType() == ObjectType::PLAYER)
		{
			m_player_index = 0;
		}

		delete gameObjects.at(index);
		gameObjects.erase(gameObjects.begin() + index);
	}
}

int Window::addObject(GameObject* object)
{
	gameObjects.push_back(object);

	return gameObjects.size() - 1;
}

int Window::addPlayer(const int x, const int y)
{
	int index = addObject(new Player(x, y, &gameObjects));
	((Player*)gameObjects.at(index))->setKeys(sf::Keyboard::A, sf::Keyboard::D,
		sf::Keyboard::S,
		sf::Keyboard::W, sf::Keyboard::Space);

	m_player_index = index;

	return index;
}

int Window::addAsteroid(const int x, const int y)
{
	//rand() % window->getSize().x, rand() % window->getSize().y, rand() % 10
	addObject(new Asteroid(x, y, rand() % 5 + 3, &gameObjects, rand() % 8 + 8));

	return gameObjects.size() - 1;
}

void Window::randomAsteroid()
{
	int index = addAsteroid(0, 0);

	sf::Vector2f position;
	sf::Vector2f velocity;

	switch (rand() % 4)
	{
		//Spawn from left
	case 0:
		position = sf::Vector2f(-gameObjects.at(index)->getRadius(), 
								rand() % window->getSize().y);
		velocity = sf::Vector2f(rand() % 3 + 1, rand() % 4 - 2);
		break;
		//Spawn from right
	case 1:
		position = sf::Vector2f(window->getSize().x + 
								gameObjects.at(index)->getRadius(), rand() % window->getSize().y);
		velocity = sf::Vector2f(-rand() % 3 - 1, rand() % 4 - 2);
		break;
		//Spawn from top
	case 2:
		position = sf::Vector2f(rand() % window->getSize().x, 
								-gameObjects.at(index)->getRadius());
		velocity = sf::Vector2f(rand() % 4 - 2, rand() % 3 + 1);
		break;
		//Spawn from bottom
	case 3:
		position = sf::Vector2f(rand() % window->getSize().x, 
								window->getSize().y + gameObjects.at(index)->getRadius());
		velocity = sf::Vector2f(rand() % 4 - 2, -rand() % 3 - 1);
		break;
	}

	gameObjects.at(index)->setPosition(position);
	gameObjects.at(index)->setVelocity(velocity);
}

void Window::deleteAllType(const ObjectType type)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects.at(i)->getType() == type)
		{
			delete gameObjects.at(i);
			gameObjects.erase(gameObjects.begin() + i);

			if (i > 0)
				i--;
		}
	}
}

void Window::startMenuLogic()
{
	while (gameObjects.size() > 0)
		deleteObject(0);

	startMenu->update();
}

void Window::gameplayLogic()
{
	bool preventDupePlayer = false;

	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects.at(i)->getType() == ObjectType::PLAYER && !preventDupePlayer)
			preventDupePlayer = true;
		else if (gameObjects.at(i)->getType() == ObjectType::PLAYER && preventDupePlayer)
		{
			deleteObject(i);
			i--;
		}

		if (gameObjects.at(i)->isAlive())
		{
			gameObjects.at(i)->update(dt * 50);

			for (int k = 0; k < gameObjects.size(); k++)
			{
				if (i >= gameObjects.size())
					i = gameObjects.size() - 1;
				if (k >= gameObjects.size())
					k = gameObjects.size() - 1;

				if (i != k && k >= 0 && k < gameObjects.size())
					if (gameObjects.at(i)->collision(*gameObjects.at(k)))
					{
						GameObject* objectOne = gameObjects.at(i);
						GameObject* objectTwo = gameObjects.at(k);

						if (objectOne->getType() == ObjectType::ASTEROID &&
							objectTwo->getType() == ObjectType::PLAYER ||
							objectOne->getType() == ObjectType::PLAYER &&
							objectTwo->getType() == ObjectType::ASTEROID)
						{
							deleteObject(i);
							deleteObject(k);

							m_player_score = 0;

							if (i > 0)
								i--;
							if (k > 0)
								k--;

							//Destroyed sound
							m_player_hit.play();

							deleteAllType(ObjectType::BULLET);
							deleteAllType(ObjectType::ASTEROID);

							gameState = GameStates::GAMEOVER;

							//addPlayer(window->getSize().x / 2, window->getSize().y / 2);
						}
						else if (objectOne->getType() == ObjectType::ASTEROID &&
							objectTwo->getType() == ObjectType::BULLET ||
							objectOne->getType() == ObjectType::BULLET &&
							objectTwo->getType() == ObjectType::ASTEROID)
						{
							m_player_score += objectOne->getRadius();

							m_explosion.play();

							deleteObject(i);
							deleteObject(k);


							if (i > 0)
								i--;
							if (k > 0)
								k--;
						}
					}
			}
		}
		else
			deleteObject(i);
	}

	if (!preventDupePlayer)
		addPlayer(window->getSize().x / 2, window->getSize().y / 2);

	/* Asteroids Spawn Rate */
	if (m_asteroid_spawn_clock.getElapsedTime().asSeconds() > m_asteroid_spawn_rate)
	{
		randomAsteroid();

		m_asteroid_spawn_clock.restart();
	}

	offScreen();

	/* Update text score */
	m_score_count.setString(std::to_string(m_player_score));
}

void Window::gameoverLogic()
{
	gameOver->update();
}
