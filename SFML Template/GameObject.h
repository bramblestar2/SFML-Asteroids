#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();

	void setPosition(const sf::Vector2f position);
	void setPosition(const float x, const float y);

	void setVelocity(const sf::Vector2f velocity);
	void setVelocity(const float x, const float y);

	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;
	bool getCollided() const;
	bool isAlive() const;
	int getTeam() const;
	float getRadius() const;

	virtual bool collision(GameObject& object); //If collided, return true

	virtual void update(const double dt) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates& states) = 0;

protected:
	void setTeam(const int team);
	void setAliveState(const bool alive);
	void setCollisionRadius(const float radius);

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	float m_collisionRadius; //Will be using radius to detect collision
	int m_team; //Dont collide objects on same team
	bool m_alive;
	bool m_collided;
};

