#pragma once
#include "GameObject.h"
#include "Bullet.h"

class Player : public GameObject
{
public:
	Player(const float x, const float y,
		std::vector<GameObject*>* objectsPtr = nullptr);
	~Player() override;

	void setPosition(const float x, const float y) override;
	void setKeys(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key brake,
		sf::Keyboard::Key forward, sf::Keyboard::Key fire);

	sf::Vector2f getPosition() const override;
	float getRotation() const;

	void updateEvents(const sf::Event& event) override;
	void update(const double dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates& states) override;

private:
	void makeSprite();

	std::vector<GameObject*>* m_gameObjectPtr;

	sf::Keyboard::Key m_turnLeft;
	sf::Keyboard::Key m_turnRight;
	sf::Keyboard::Key m_moveForward;
	sf::Keyboard::Key m_brake;
	sf::Keyboard::Key m_fire;

	sf::ConvexShape m_sprite_player;
	sf::ConvexShape m_sprite_burner;

	float m_current_speed;
	float m_max_speed;
};

