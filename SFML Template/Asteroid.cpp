#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid(const float x, const float y, const int size, const int randomized_points) 
	: GameObject(), m_sprite(randomized_points)
{
	GameObject::setCollisionRadius(size * 5);
	GameObject::setTeam(2);
	GameObject::setPosition(x, y);

	//Set sprite center
	//m_sprite.setOrigin(m_sprite.getRadius(), m_sprite.getRadius());
	m_sprite.setOutlineColor(sf::Color::White);
	m_sprite.setFillColor(sf::Color::Transparent);
	m_sprite.setOutlineThickness(3);
	m_sprite.setPosition(x, y);

	makeSprite(randomized_points);
}

Asteroid::~Asteroid()
{
}

void Asteroid::update(const double dt)
{
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	target.draw(m_sprite, states);
}

void Asteroid::makeSprite(const int points)
{
	for (int i = 0; i < points; i++)
	{
		float xDistance = sin(360 / points * i) * GameObject::getRadius();
		float yDistance = cos(360 / points * i) * GameObject::getRadius();

		m_sprite.setPoint(i, sf::Vector2f(xDistance, yDistance));
	}
}
