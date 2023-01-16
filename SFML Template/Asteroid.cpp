#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid(const float x, const float y, const int size, const int randomized_points) : GameObject()
{
	GameObject::setCollisionRadius(size * 5);
	GameObject::setTeam(2);
	GameObject::setPosition(x, y);

	makeSprite(randomized_points);
}

Asteroid::~Asteroid()
{
}

void Asteroid::update(const double dt)
{
	sf::Vector2f vel = GameObject::getVelocity();
	GameObject::setPosition((vel.x * dt) + GameObject::getPosition().x, 
							(vel.y * dt) + GameObject::getPosition().y);

	for (int i = 0; i < m_sprite.getVertexCount(); i++)
	{
		m_sprite[i].position += sf::Vector2f(vel.x * dt, vel.y * dt);
	}
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	target.draw(m_sprite, states);
}

void Asteroid::makeSprite(const int points)
{
	m_sprite = sf::VertexArray(sf::LinesStrip, points);

	int index = 0;
	for (int i = 0; i < 360; i += 360/points)
	{
		float xpos, ypos;
		xpos = sin(i) * GameObject::getRadius() + GameObject::getPosition().x;
		ypos = cos(i) * GameObject::getRadius() + GameObject::getPosition().y;

		m_sprite[index].position = sf::Vector2f(xpos, ypos);
		m_sprite[index].color = sf::Color(255,255,255,255);

		index++;
	}
}
