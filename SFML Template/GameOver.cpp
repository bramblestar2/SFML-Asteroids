#include "GameOver.h"
//testtesttest
GameOver::GameOver(const sf::Vector2f render_size)
{
	m_select_up = sf::Keyboard::W;
	m_select_down = sf::Keyboard::S;
	m_select_enter = sf::Keyboard::Space;

	Menu::setDefaultColor(sf::Color::White);
	Menu::setSelectedColor(sf::Color::Red);
	Menu::setDefaultSize(30);
	Menu::setSelectedSize(40);

	Menu::setFonts(*FontHandler::getFont("GameFont"));

	Menu::addSelection("GAME OVER");
	Menu::addSelection("Restart");
	Menu::addSelection("Quit");

	Menu::setTextDistance(50);

	Menu::addNonSelectable(0);
	Menu::setSelected(1);
	
	Menu::updateText();
	Menu::centerText(render_size);

	m_select_sound_buffer.loadFromFile("menu_select.wav");
	m_select_sound.setBuffer(m_select_sound_buffer);

	m_enter_sound_buffer.loadFromFile("menu_enter.wav");
	m_enter_sound.setBuffer(m_enter_sound_buffer);
}

GameOver::~GameOver()
{
}

void GameOver::setOnClose(std::function<void()>& onClose)
{
	m_onClose = onClose;
}

void GameOver::setOnRestart(std::function<void()>& onRestart)
{
	m_onRestart = onRestart;
}

void GameOver::setControls(const sf::Keyboard::Key up, const sf::Keyboard::Key down, const sf::Keyboard::Key enter)
{
	m_select_up = up;
	m_select_down = down;
	m_select_enter = enter;
}

void GameOver::update()
{
}

void GameOver::updateEvents(sf::Event& event)
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

			if (Menu::getSelected() == 1) //Restart
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

void GameOver::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	for (int i = 0; i < Menu::getSelections()->size(); i++)
	{
		target.draw(Menu::getSelections()->at(i), states);
	}
}
