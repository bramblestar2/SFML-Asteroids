#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "../FontHandler.h"
#include "../Asteroid.h"
#include "../Player.h"
#include "../Bullet.h"
#include "../StartMenu.h"

class Window
{
	enum class GameStates
	{
		START_MENU,
		GAMEPLAY,
		GAMEOVER
	};

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

	int addPlayer(const int x, const int y);
	int m_player_index;

	int addAsteroid(const int x, const int y); // returns the index the asteroid is at
	void randomAsteroid();

	void deleteAllType(const ObjectType type);

	/* GAME METHODS */
	void startMenuLogic();
	void gameplayLogic();
	void gameoverLogic();

	std::vector<GameObject*> gameObjects;

	sf::Clock dtClock;
	double dt;

	sf::RenderWindow* window;
	sf::Event event;
	
	sf::Shader shader;

	sf::Clock m_asteroid_spawn_clock;
	float m_asteroid_spawn_rate;

	sf::Font m_game_font;
	sf::Text m_score_count;

	int m_player_score;

	sf::Sound m_player_hit, m_explosion;
	sf::SoundBuffer m_player_hit_buffer, m_explosion_buffer;

	//0: Start menu
	//1: Gameplay
	//2: Game Over
	GameStates gameState;
	StartMenu* startMenu;
};

