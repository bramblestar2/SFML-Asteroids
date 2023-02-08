#pragma once
#include "Menu.h"
#include <fstream>
#include <functional>
#include <SFML/Audio.hpp>

class GameOver : public Menu
{
public:
	GameOver();
	~GameOver();

	void setOnClose(std::function<void()>& onClose);
	void setOnRestart(std::function<void()>& onRestart);

	void setControls(const sf::Keyboard::Key up, const sf::Keyboard::Key down,
					 const sf::Keyboard::Key enter);

	void update() override;
	void updateEvents(sf::Event& event) override;
	void draw(sf::RenderTarget& target, sf::RenderStates& states) override;

private:
	sf::Sound m_select_sound, m_enter_sound;
	sf::SoundBuffer m_select_sound_buffer, m_enter_sound_buffer;

	sf::Keyboard::Key m_select_up;
	sf::Keyboard::Key m_select_down;
	sf::Keyboard::Key m_select_enter;

	std::function<void()> m_onClose;
	std::function<void()> m_onRestart;
};

