#pragma once
#include <SFML/Graphics.hpp>
#include "../Asteroid.h"

class Window
{
public:
	Window();
	//Free memory
	virtual ~Window();

	void run();
	void render();
	void update();
	void updateDt();
	void updateSFMLEvents();
private:
	void initWindow();
	
	Asteroid asteroid;

	sf::Clock dtClock;
	double dt;

	sf::RenderWindow* window;
	sf::Event event;
};

