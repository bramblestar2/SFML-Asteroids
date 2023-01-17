#pragma once
#include "GameObject.h"

class Asteroid : public GameObject
{
public:
	Asteroid(const float x, const float y, const int size, 
			 const int randomized_points = rand() % 4 + 4);
	~Asteroid() override;

	void setPosition(const float x, const float y) override;
	sf::Vector2f getPosition() const override;

	void update(const double dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates& states) override;

private:
	void makeSprite(const int points);

	sf::ConvexShape m_sprite;

	int lifetime;
};

