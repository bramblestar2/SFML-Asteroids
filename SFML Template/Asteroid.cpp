#include "Asteroid.h"
#include <iostream>
#include <time.h>

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

	lifetime = 500;
}

Asteroid::~Asteroid()
{
	std::cout << "Asteroid destroyed" << std::endl;
}

void Asteroid::setPosition(const float x, const float y)
{
	m_sprite.setPosition(x, y);
}

sf::Vector2f Asteroid::getPosition() const
{
	return m_sprite.getPosition();
}

void Asteroid::update(const double dt)
{
	if (GameObject::isAlive())
	{
		sf::Vector2f vel = GameObject::getVelocity();
		m_sprite.move((vel.x / (GameObject::getRadius() / 10)) * dt, (vel.y / (GameObject::getRadius() / 10)) * dt);

		//m_sprite.rotate((GameObject::getRadius() / 10) * dt);

		if (lifetime > 0 && GameObject::isAlive())
			lifetime--;
		else if (lifetime <= 0 && GameObject::isAlive())
		{
			GameObject::setAliveState(false);
			m_sprite.setScale(0, 0);
		}

		GameObject::setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y);
	}
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	target.draw(m_sprite, states);
}

void Asteroid::makeSprite(const int points)
{
	float degrees = 360 / points;

	for (int i = 0; i < points; i++)
	{
		float radians = (degrees * i) * (3.14 / 180);

		float xDistance = sin(radians) * (GameObject::getRadius() * (fmod(rand(), 0.6) + 0.4));
		float yDistance = cos(radians) * (GameObject::getRadius() * (fmod(rand(), 0.6) + 0.4));

		m_sprite.setPoint(i, sf::Vector2f(xDistance, yDistance));
	}
}
