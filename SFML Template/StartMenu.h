#pragma once
#include "Menu.h"
#include "FontHandler.h"
#include <SFML/Audio.hpp>
#include <functional>

class StartMenu : public Menu
{
public:
	StartMenu(const sf::Vector2f window_size);
	~StartMenu();

	void setOnClose(const std::function<void()> onClose);
	void setOnStart(const std::function<void()> onStart);

	void setControls(const sf::Keyboard::Key up, const sf::Keyboard::Key down, 
					const sf::Keyboard::Key enter);

	void update() override;
	void updateEvents(sf::Event& event) override;
	void draw(sf::RenderTarget& target, sf::RenderStates& states) override;

private:
	sf::Keyboard::Key m_select_up;
	sf::Keyboard::Key m_select_down;
	sf::Keyboard::Key m_select_enter;

	std::function<void()> m_onClose;
	std::function<void()> m_onStart;

	sf::Sound m_select_sound, m_enter_sound;
	sf::SoundBuffer m_select_sound_buffer, m_enter_sound_buffer;
};

