#include "Asteroid.h"
#include <iostream>
#include <time.h>

Asteroid::Asteroid(const float x, const float y, const int size, 
	std::vector<GameObject*>* objectsPtr, const int randomized_points)
	: GameObject(), m_sprite(randomized_points)
{
	GameObject::setType(ObjectType::ASTEROID);
	GameObject::setCollisionRadius(size * 5);
	GameObject::setTeam(2);
	GameObject::setPosition(x, y);
	m_size = size;
	gameObjectsPtr = objectsPtr;

	//Set sprite center
	//m_sprite.setOrigin(m_sprite.getRadius(), m_sprite.getRadius());
	m_sprite.setOutlineColor(sf::Color::White);
	m_sprite.setFillColor(sf::Color::Transparent);
	m_sprite.setOutlineThickness(3);
	m_sprite.setPosition(x, y);

	makeSprite(randomized_points);

	m_lifetime = 500;
}

Asteroid::~Asteroid()
{
	if (this->m_size > 3 && GameObject::getCollided())
	{
		//Make two asteroids and add to list
		//Randomize both asteroids velocities
		int index;
		for (int i = 0; i < 2; i++)
		{
			gameObjectsPtr->push_back(new Asteroid(m_sprite.getPosition().x,
				m_sprite.getPosition().y, m_size - 1, gameObjectsPtr));
			index = gameObjectsPtr->size() - 1;
			gameObjectsPtr->at(index)->setVelocity(rand() % 6 - 3, rand() % 6 - 3);
		}
	}
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
		if (GameObject::getCollided())
			GameObject::setAliveState(false);

		sf::Vector2f vel = GameObject::getVelocity();
		m_sprite.move((vel.x / (GameObject::getRadius() / 10)) * dt, (vel.y / (GameObject::getRadius() / 10)) * dt);

		//m_sprite.rotate((GameObject::getRadius() / 10) * dt);

		if (m_lifetime > 0 && GameObject::isAlive())
			m_lifetime--;
		else if (m_lifetime <= 0 && GameObject::isAlive())
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
