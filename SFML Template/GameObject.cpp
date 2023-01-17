#include "GameObject.h"
#include <math.h>
#include <iostream>

GameObject::GameObject()
{
	m_type = ObjectType::NONE;
	m_alive = true;
	m_collided = false;
	m_collisionRadius = 0;
	m_team = -1;
	m_collidable = true;
}

GameObject::~GameObject()
{
}

void GameObject::setTeam(const int team)
{
	m_team = team;
}

void GameObject::setAliveState(const bool alive)
{
	m_alive = alive;
}

void GameObject::setCollisionRadius(const float radius)
{
	m_collisionRadius = radius;
}

void GameObject::setType(const ObjectType type)
{
	m_type = type;
}

void GameObject::setCollidable(const bool collidable)
{
	m_collidable = collidable;
}

void GameObject::setPosition(const sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

void GameObject::setPosition(const float x, const float y)
{
	m_position.x = x;
	m_position.y = y;
}

void GameObject::setVelocity(const sf::Vector2f velocity)
{
	setVelocity(velocity.x, velocity.y);
}

void GameObject::setVelocity(const float x, const float y)
{
	m_velocity.x = x;
	m_velocity.y = y;
}

ObjectType GameObject::getType() const
{
	return m_type;
}

sf::Vector2f GameObject::getPosition() const
{
	return m_position;
}

sf::Vector2f GameObject::getVelocity() const
{
	return m_velocity;
}

bool GameObject::getCollided() const
{
	return m_collided;
}

bool GameObject::isAlive() const
{
	return m_alive;
}

bool GameObject::getCollidable() const
{
	return m_collidable;
}

int GameObject::getTeam() const
{
	return m_team;
}

float GameObject::getRadius() const
{
	return m_collisionRadius;
}

bool GameObject::collision(GameObject& object)
{
	if (object.getCollidable())
	{
		float distanceX = pow(object.m_position.x - m_position.x, 2);
		float distanceY = pow(object.m_position.y - m_position.y, 2);

		//std::cout << object.m_position.x << " - " << object.m_position.y << std::endl;
		//std::cout << m_position.x << " - " << m_position.y << std::endl;

		float totalDistance = sqrt(distanceX + distanceY);

		if (totalDistance < this->m_collisionRadius)
		{
			if (object.m_team < 1 || object.m_team == this->m_team)
			{
				return false;
			}
			else
			{
				this->m_collided = true;
				object.m_collided = true;

				return true;
			}
		}
	}
	return false;
}

void GameObject::updateEvents(const sf::Event& event)
{
}
