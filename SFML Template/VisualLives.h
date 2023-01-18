#pragma once
#include "Player.h"
#include <vector>

class VisualLives
{
public:
	VisualLives(const int lives);
	~VisualLives();

	int getLives() const;

	void setLives(const int count);
	void addLives(const int count);
	void removeLives(const int count);

	void draw(sf::RenderTarget& target, sf::RenderStates& states);

private:
	int m_lives;
	std::vector<Player> m_prop_players;
};

