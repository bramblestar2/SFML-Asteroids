#include "StartMenu.h"
#include <thread>

StartMenu::StartMenu(const sf::Vector2f window_size)
{
	m_select_up = sf::Keyboard::W;
	m_select_down = sf::Keyboard::S;
	m_select_enter = sf::Keyboard::Space;

	Menu::setDefaultColor(sf::Color::White);
	Menu::setSelectedColor(sf::Color::Red);
	Menu::setDefaultSize(30);
	Menu::setSelectedSize(40);
	
	sf::Text menuText;
	menuText.setString("MENU");
	Menu::addSelection(menuText);
	Menu::addNonSelectable(0);

	sf::Text startText, quitText;
	startText.setString("Start");
	quitText.setString("Quit");

	Menu::addSelection(startText);
	Menu::addSelection(quitText);
	sf::Font font = *FontHandler::getFont("GameFont");
	font.loadFromFile("KarmaFuture.ttf");
	Menu::setFonts(font);

	Menu::setSelected(1);

	Menu::updateText();
	Menu::centerText(window_size);

	m_select_sound_buffer.loadFromFile("menu_select.wav");
	m_select_sound.setBuffer(m_select_sound_buffer);

	m_enter_sound_buffer.loadFromFile("menu_enter.wav");
	m_enter_sound.setBuffer(m_enter_sound_buffer);
}

StartMenu::~StartMenu()
{
}

void StartMenu::setOnClose(const std::function<void()> onClose)
{
	m_onClose = onClose;
}

void StartMenu::setOnStart(const std::function<void()> onStart)
{
	m_onStart = onStart;
}

void StartMenu::setControls(const sf::Keyboard::Key up, const sf::Keyboard::Key down, 
							const sf::Keyboard::Key enter)
{
	m_select_up = up;
	m_select_down = down;
	m_select_enter = enter;
}

void StartMenu::update()
{
}

void StartMenu::updateEvents(sf::Event& event)
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
				if (Menu::setSelected(Menu::getSelected()+1))
					m_select_sound.play();
			}
		}
		else if (event.key.code == m_select_enter)
		{
			if (Menu::getSelected() == 1) //Start
			{
				m_enter_sound.play();

				if (m_onStart)
					m_onStart();
			}
			else if (Menu::getSelected() == 2) //Quit
			{
				m_enter_sound.play();

				while (m_enter_sound.getStatus() == sf::Sound::Playing) {}
				
				//long long seconds = m_enter_sound_buffer.getDuration().asSeconds() - m_enter_sound.getPlayingOffset().asSeconds();
				//
				//std::this_thread::sleep_for(std::chrono::seconds(seconds));

				if (m_onClose)
					m_onClose();
			}
		}

		Menu::updateText();
	}
}

void StartMenu::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	for (int i = 0; i < Menu::getSelections()->size(); i++)
	{
		target.draw(Menu::getSelections()->at(i), states);
	}
}
