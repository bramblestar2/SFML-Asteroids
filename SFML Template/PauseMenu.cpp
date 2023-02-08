#include "PauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu(const sf::Vector2f render_size)
{
	m_select_up = sf::Keyboard::W;
	m_select_down = sf::Keyboard::S;
	m_select_enter = sf::Keyboard::Space;

	Menu::setDefaultColor(sf::Color::White);
	Menu::setSelectedColor(sf::Color::Red);
	Menu::setDefaultSize(30);
	Menu::setSelectedSize(40);

	Menu::setFonts(*FontHandler::getFont("GameFont"));

	Menu::addSelection("Unpause");
	Menu::addSelection("Restart");
	Menu::addSelection("Quit");

	Menu::setTextDistance(50);

	Menu::updateText();
	Menu::centerText(render_size);


	m_select_sound_buffer.loadFromFile("menu_select.wav");
	m_select_sound.setBuffer(m_select_sound_buffer);

	m_enter_sound_buffer.loadFromFile("menu_enter.wav");
	m_enter_sound.setBuffer(m_enter_sound_buffer);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::setOnClose(const std::function<void()> onClose)
{
	m_onClose = onClose;
}

void PauseMenu::setOnRestart(const std::function<void()> onRestart)
{
	m_onRestart = onRestart;
}

void PauseMenu::setOnUnpause(const std::function<void()> onUnpause)
{
	m_onUnpause = onUnpause;
}

void PauseMenu::setControls(const sf::Keyboard::Key up, const sf::Keyboard::Key down, const sf::Keyboard::Key enter)
{
	m_select_up = up;
	m_select_down = down;
	m_select_enter = enter;
}

void PauseMenu::update()
{
}

void PauseMenu::updateEvents(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		bool inBoundsUp = Menu::getSelected() > 0;
		bool inBoundsDown = Menu::getSelected() < Menu::getSelections()->size() - 1;
		if (event.key.code == m_select_up)
		{
			if (inBoundsUp)
			{
				if (Menu::setSelected(Menu::getSelected() - 1))
					m_select_sound.play();
			}
		}
		else if (event.key.code == m_select_down)
		{
			if (inBoundsDown)
			{
				if (Menu::setSelected(Menu::getSelected() + 1))
					m_select_sound.play();
			}
		}
		else if (event.key.code == m_select_enter)
		{
			m_enter_sound.play();

			if (Menu::getSelected() == 0) //Unpause
			{
				if (m_onUnpause)
					m_onUnpause();
			}
			else if (Menu::getSelected() == 1) //Restart
			{
				if (m_onRestart)
					m_onRestart();
			}
			else if (Menu::getSelected() == 2) //Quit
			{
				m_enter_sound.play();

				while (m_enter_sound.getStatus() == sf::Sound::Playing) {}

				if (m_onClose)
					m_onClose();
			}
		}

		Menu::updateText();
	}
}

void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	sf::RectangleShape darkenBackground(sf::Vector2f(target.getSize()));
	darkenBackground.setFillColor(sf::Color(0, 0, 0, 100));
	target.draw(darkenBackground);

	for (int i = 0; i < Menu::getSelections()->size(); i++)
	{
		target.draw(Menu::getSelections()->at(i), states);
	}
}
