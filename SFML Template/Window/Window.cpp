#include "Window.h"
#include <time.h>

Window::Window() : asteroid(100,100,3,5)
{
	srand(time(NULL));

	initWindow();
}

Window::~Window()
{
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

	asteroid.draw(*window, states);

	window->display();
}

void Window::update()
{
	asteroid.update(dt);
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
				}
				break;
		}
	}
}

void Window::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(500, 300), "TITLE", sf::Style::Default);
}
