#pragma once
#include <SFML/Graphics.hpp>
#include "../Asteroid.h"
#include <vector>

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


	void offScreen();
	bool offTop(const GameObject& object);
	bool offBottom(const GameObject& object);
	bool offLeft(const GameObject& object);
	bool offRight(const GameObject& object);
	
	void deleteObject(const int index);
	void addObject(GameObject* object);

	int addAsteroid(const int x, const int y); // returns the index the asteroid is at
	void randomAsteroid();

	std::vector<GameObject*> gameObjects;

	sf::Clock dtClock;
	double dt;

	sf::RenderWindow* window;
	sf::Event event;
};

