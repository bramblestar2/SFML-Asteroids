#include "Window.h"
#include <time.h>'
#include <iostream>

Window::Window()
{
	srand(time(NULL));

	initWindow();
}

Window::~Window()
{
	while (gameObjects.size() > 0)
		deleteObject(0);

	delete window;
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

	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects.at(i)->draw(*window, states);

	window->display();
}

void Window::update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects.at(i)->isAlive())
		{
			gameObjects.at(i)->update(dt * 50);

			for (int k = 0; k < gameObjects.size(); k++)
			{
				if (k != i)
					if (gameObjects.at(i)->collision(*gameObjects.at(k)))
					{
						deleteObject(i);
						i--;
					}
			}
		}
		else
			deleteObject(i);
	}

	offScreen();
}

void Window::updateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Window::updateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
				window->close();
				break;
		case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
						window->close();
						break;

				case sf::Keyboard::Space:
					randomAsteroid();
					break;
				}
				break;
		}
	}
}

void Window::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(500, 300), "Asteroids", sf::Style::Default);
	window->setFramerateLimit(60);
}

void Window::offScreen()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (offTop(*gameObjects.at(i)))
		{
			std::cout << "Top" << std::endl;
			gameObjects.at(i)->setPosition(gameObjects.at(i)->getPosition().x, window->getSize().y + gameObjects.at(i)->getRadius());
		}
		else if (offBottom(*gameObjects.at(i)))
		{
			std::cout << "Bottom" << std::endl;
			gameObjects.at(i)->setPosition(gameObjects.at(i)->getPosition().x, -gameObjects.at(i)->getRadius());
		}

		if (offLeft(*gameObjects.at(i)))
		{
			std::cout << "Left" << std::endl;
			gameObjects.at(i)->setPosition(window->getSize().x + gameObjects.at(i)->getRadius(), gameObjects.at(i)->getPosition().y);
		}
		else if (offRight(*gameObjects.at(i)))
		{
			std::cout << "Right" << std::endl;
			gameObjects.at(i)->setPosition(-gameObjects.at(i)->getRadius(), gameObjects.at(i)->getPosition().y);
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
	delete gameObjects.at(index);
	gameObjects.erase(gameObjects.begin() + index);
}

void Window::addObject(GameObject* object)
{
	gameObjects.push_back(object);
}

int Window::addAsteroid(const int x, const int y)
{
	//rand() % window->getSize().x, rand() % window->getSize().y, rand() % 10
	addObject(new Asteroid(x, y, rand() % 5 + 3, rand() % 8 + 8));

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
