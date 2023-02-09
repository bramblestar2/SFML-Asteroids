#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include <SFML/Audio.hpp>

class Player : public GameObject
{
public:
	Player(const float x, const float y,
		std::vector<GameObject*>* objectsPtr = nullptr);
	~Player() override;

	void setPosition(const float x, const float y) override;
	void setKeys(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key brake,
		sf::Keyboard::Key forward, sf::Keyboard::Key fire);
	void setSmoothTurn(const bool smooth);

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

	sf::Vector2f m_velocity;
	float m_rotationSpeed;

	sf::Clock m_bullet_clock, m_reload_clock;
	float m_firerate, m_reload_time_1, m_reload_time_2;
	int m_bullet_count, m_max_bullets;
	bool m_reloading;

	float m_current_speed;
	float m_max_speed;

	bool m_sharpTurn;

	sf::Sound m_fire_sound, m_reloaded_sound, m_single_reload, m_booster_sound;
	sf::SoundBuffer m_fire_sound_buffer, m_reloaded_sound_buffer, 
					m_single_reload_buffer, m_booster_sound_buffer;
};

