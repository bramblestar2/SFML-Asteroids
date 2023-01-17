#include "Bullet.h"
#include <iostream>

Bullet::Bullet(const double x, const double y,
	const float rotation, const float speed) : m_sprite(sf::Points, 1)
{
	GameObject::setPosition(x, y);
	GameObject::setType(ObjectType::BULLET);
	GameObject::setCollidable(true);
	GameObject::setCollisionRadius(5);
	GameObject::setTeam(1);

	m_speed = speed;
	m_sprite[0].position = sf::Vector2f(x, y);
	m_rotation = 0;


	float radians = rotation * (3.14 / 180);
	GameObject::setVelocity(sin(radians) * speed, -cos(radians) * speed);

	m_lifetime = 400;
}

Bullet::~Bullet()
{
}

void Bullet::setPosition(const sf::Vector2f position)
{
	m_sprite[0].position = position;
	GameObject::setPosition(position.x, position.y);
}

void Bullet::update(const double dt)
{
	if (GameObject::isAlive())
	{
		if (m_lifetime > 0)
			m_lifetime--;
		else
			GameObject::setAliveState(false);

		if (GameObject::getCollided())
			GameObject::setAliveState(false);

		sf::Vector2f newPos;
		newPos.x = GameObject::getPosition().x + (GameObject::getVelocity().x * dt);
		newPos.y = GameObject::getPosition().y + (GameObject::getVelocity().y * dt);

		m_sprite[0].position = newPos;
		GameObject::setPosition(newPos);
	}
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	target.draw(m_sprite);
}

void Bullet::makeSprite()
{
	//m_sprite.setFillColor(sf::Color::Transparent);
	//m_sprite.setOutlineColor(sf::Color::White);
	//
	//m_sprite.setPoint(0, sf::Vector2f(0, 1));
	//m_sprite.setPoint(0, sf::Vector2f(0, -1));
}
