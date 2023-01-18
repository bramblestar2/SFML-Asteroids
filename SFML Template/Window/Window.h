#pragma once
#include <SFML/Graphics.hpp>
#include "../Asteroid.h"
#include "../Player.h"
#include "../Bullet.h"
#include <vector>
#include <thread>

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
	int addObject(GameObject* object); //returns the index the asteroid is at

	int addAsteroid(const int x, const int y); // returns the index the asteroid is at
	void randomAsteroid();

	std::vector<GameObject*> gameObjects;

	sf::Clock dtClock;
	double dt;

	sf::RenderWindow* window;
	sf::Event event;
	
	sf::Shader shader;

	sf::Clock m_asteroid_spawn_clock;
	float m_asteroid_spawn_rate;


	std::thread* renderingThread;
};

