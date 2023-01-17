#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(const float x, const float y);
	~Player();

	void update(const double dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates& states) override;

private:
	sf::Keyboard::Key turnLeft;
	sf::Keyboard::Key turnRight;
	sf::Keyboard::Key moveForward;

	sf::ConvexShape m_sprite;

	float m_speed;
};

