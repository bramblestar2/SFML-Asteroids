#pragma once
#include "Menu.h"
#include "FontHandler.h"
#include <SFML/Audio.hpp>
#include <functional>

class PauseMenu : public Menu
{
public:
	PauseMenu(const sf::Vector2f render_size);
	~PauseMenu();

	void setOnClose(const std::function<void()> onClose);
	void setOnRestart(const std::function<void()> onRestart);
	void setOnUnpause(const std::function<void()> onUnpause);

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
	std::function<void()> m_onRestart;
	std::function<void()> m_onUnpause;

	sf::Sound m_select_sound, m_enter_sound;
	sf::SoundBuffer m_select_sound_buffer, m_enter_sound_buffer;
};

