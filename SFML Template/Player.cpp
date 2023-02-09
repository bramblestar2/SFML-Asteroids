#include "Player.h"
#include <iostream>

Player::Player(const float x, const float y,
		std::vector<GameObject*>* objectsPtr) : m_sprite_player(3), m_sprite_burner(3)
{
	GameObject::setType(ObjectType::PLAYER);
	GameObject::setCollisionRadius(15);
	GameObject::setTeam(1);
	GameObject::setPosition(x, y);

	m_turnLeft = sf::Keyboard::Unknown;
	m_turnRight = sf::Keyboard::Unknown;
	m_moveForward = sf::Keyboard::Unknown;

	m_max_speed = 6.f;
	m_current_speed = 0.f;
	m_gameObjectPtr = objectsPtr;

	makeSprite();
	setPosition(x, y);


	m_sharpTurn = true;
	m_reloading = false;
	m_max_bullets = 10;
	m_bullet_count = m_max_bullets;

	m_firerate = 0.15;
	m_reload_time_1 = 0.2;
	m_reload_time_2 = m_reload_time_1 * m_max_bullets + 0.6;
	//m_reload_time_2 = 2.5;

	m_fire_sound_buffer.loadFromFile("shoot.wav");
	m_fire_sound.setBuffer(m_fire_sound_buffer);
	m_fire_sound.setVolume(60);

	m_reloaded_sound_buffer.loadFromFile("reloaded.wav");
	m_reloaded_sound.setBuffer(m_reloaded_sound_buffer);

	m_single_reload_buffer.loadFromFile("singleReload.wav");
	m_single_reload.setBuffer(m_single_reload_buffer);
	m_single_reload.setVolume(20);

	m_booster_sound_buffer.loadFromFile("booster.wav");
	m_booster_sound.setBuffer(m_booster_sound_buffer);
}

Player::~Player()
{
}

void Player::setPosition(const float x, const float y)
{
	m_sprite_burner.setPosition(x, y);
	m_sprite_player.setPosition(x, y);
}

void Player::setKeys(sf::Keyboard::Key left, sf::Keyboard::Key right, 
					 sf::Keyboard::Key brake,
					 sf::Keyboard::Key forward, sf::Keyboard::Key fire)
{
	m_turnLeft = left;
	m_turnRight = right;
	m_moveForward = forward;
	m_brake = brake;
	m_fire = fire;
}

void Player::setSmoothTurn(const bool smooth)
{
	m_sharpTurn = !smooth;
}

sf::Vector2f Player::getPosition() const
{
	return m_sprite_player.getPosition();
}

float Player::getRotation() const
{
	return m_sprite_player.getRotation();
}

void Player::updateEvents(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
	}
}

void Player::update(const double dt)
{
	if (GameObject::isAlive())
	{
		/* BULLET FIRE LOGIC */
		if (m_reload_clock.getElapsedTime().asSeconds() > m_reload_time_1 && !m_reloading)
		{
			if (m_bullet_count < m_max_bullets)
			{
				m_bullet_count++;
				m_single_reload.play();
			}
			m_reload_clock.restart();
		}
		else if (m_reload_clock.getElapsedTime().asSeconds() > m_reload_time_2 && m_reloading)
		{
			m_reloading = false;
			m_bullet_count = m_max_bullets;
			m_reloaded_sound.play();
			m_reload_clock.restart();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_gameObjectPtr != nullptr)
		{
			if (!m_reloading && m_bullet_clock.getElapsedTime().asSeconds() > m_firerate)
			{
				m_gameObjectPtr->push_back(new Bullet(m_sprite_player.getPosition().x,
					m_sprite_player.getPosition().y, m_sprite_player.getRotation(), 5 + 
					((abs(m_velocity.x) + abs(m_velocity.y))/2)));

				m_bullet_count--;

				if (m_bullet_count <= 0)
					m_reloading = true;

				m_fire_sound.play();

				m_reload_clock.restart();
				m_bullet_clock.restart();
			}
		}

		/* PLAYER MOVEMENT */
		float radians = m_sprite_player.getRotation() * (3.14 / 180);

		float rotationMaxSpeed = 6;

		if (sf::Keyboard::isKeyPressed(m_turnLeft))
		{
			m_rotationSpeed = m_rotationSpeed + (0.05 * dt) * (-rotationMaxSpeed - m_rotationSpeed);
			if (m_sharpTurn) 
			{
				m_sprite_player.rotate(-rotationMaxSpeed * dt);
				m_sprite_burner.rotate(-rotationMaxSpeed * dt);
			}
		}
		else if (sf::Keyboard::isKeyPressed(m_turnRight))
		{
			m_rotationSpeed = m_rotationSpeed + (0.05 * dt) * (rotationMaxSpeed - m_rotationSpeed);
			if (m_sharpTurn)
			{
				m_sprite_player.rotate(rotationMaxSpeed * dt);
				m_sprite_burner.rotate(rotationMaxSpeed * dt);
			}
		}
		else
		{
			m_rotationSpeed = m_rotationSpeed + (0.1 * dt) * (0 - m_rotationSpeed);
		}

		if (sf::Keyboard::isKeyPressed(m_moveForward))
		{
			//a = point a
			//b = point b
			//t = time
			//a + t * (b - a)

			if (m_booster_sound.getStatus() != m_booster_sound.Playing)
			{
				m_booster_sound.setLoop(true);
				m_booster_sound.play();
			}

			m_current_speed = m_current_speed + 0.01 * (m_max_speed - m_current_speed);


			m_velocity.x = m_velocity.x + (0.01 * dt) * ((sin(radians) * m_max_speed) - m_velocity.x);
			m_velocity.y = m_velocity.y + (0.01 * dt) * ((-cos(radians) * m_max_speed) - m_velocity.y);
		}
		else if (!sf::Keyboard::isKeyPressed(m_moveForward))
		{
			if (m_booster_sound.getStatus() == m_booster_sound.Playing)
			{
				m_booster_sound.setLoop(false);
			}

			float time = 0.01;

			if (sf::Keyboard::isKeyPressed(m_brake))
				time *= 5;

			m_current_speed = m_current_speed + (time * dt) * (0 - m_current_speed);

			m_velocity.x = m_velocity.x + (time * dt) * (0 - m_velocity.x);
			m_velocity.y = m_velocity.y + (time * dt) * (0 - m_velocity.y);
		}

		m_sprite_player.move(m_velocity.x * dt, m_velocity.y * dt);
		m_sprite_burner.move(m_velocity.x * dt, m_velocity.y * dt);

		if (!m_sharpTurn)
		{
			m_sprite_player.rotate(m_rotationSpeed * dt);
			m_sprite_burner.rotate(m_rotationSpeed * dt);
		}

		GameObject::setPosition(m_sprite_player.getPosition().x,
			m_sprite_player.getPosition().y);

		if (m_current_speed > 0.3)
		{
			m_sprite_burner.setOutlineColor(sf::Color::White);
		}
		else
		{
			m_sprite_burner.setOutlineColor(sf::Color::Transparent);
		}

		float burnerSize = ((m_current_speed < 0.395 ? 0.395 : m_current_speed) * 15) * 2;
		m_sprite_burner.setPoint(1, sf::Vector2f(0 * 2, (burnerSize > 20 ? 20 : burnerSize)));
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	sf::RectangleShape bulletsRemaining;
	bulletsRemaining.setSize(sf::Vector2f(30, 3));
	bulletsRemaining.setOrigin(bulletsRemaining.getSize().x / 2, bulletsRemaining.getSize().y / 2);
	bulletsRemaining.setPosition(m_sprite_player.getPosition().x, m_sprite_player.getPosition().y + 20);
	bulletsRemaining.setScale((float)m_bullet_count/(float)m_max_bullets, 1);
	bulletsRemaining.setOutlineColor(sf::Color::White);
	bulletsRemaining.setOutlineThickness(1);
	bulletsRemaining.setFillColor(sf::Color::Transparent);

	target.draw(bulletsRemaining);

	target.draw(m_sprite_burner, states);
	target.draw(m_sprite_player, states);
}

void Player::makeSprite()
{
	float size = 2;

	m_sprite_player.setFillColor(sf::Color::Transparent);
	m_sprite_player.setOutlineColor(sf::Color::White);
	m_sprite_player.setOutlineThickness(1);
	m_sprite_player.setPoint(0, sf::Vector2f(-3 * size,  5 * size));	//		  *
	m_sprite_player.setPoint(1, sf::Vector2f( 0 * size, -5 * size));	//		 / \ 
	m_sprite_player.setPoint(2, sf::Vector2f( 3 * size,  5 * size));	//		* - *

	m_sprite_burner.setFillColor(sf::Color::Transparent);
	m_sprite_burner.setOutlineColor(sf::Color::White);
	m_sprite_burner.setOutlineThickness(0.8);
	m_sprite_burner.setPoint(0, sf::Vector2f(-2 * size, 5 * size));		//		 __
	m_sprite_burner.setPoint(1, sf::Vector2f(0 * size, 9 * size));		//		 \/
	m_sprite_burner.setPoint(2, sf::Vector2f(2 * size, 5 * size));		//		  
}
