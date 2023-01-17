#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(const double x, const double y, 
		const float rotation, const float speed);
	~Bullet() override;

	void setPosition(const sf::Vector2f position) override;

	void update(const double dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates& states) override;

private:
	void makeSprite();

	int m_lifetime;
	float m_speed;
	float m_rotation;

	sf::VertexArray m_sprite;
};

