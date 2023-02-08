#include "GameOver.h"

GameOver::GameOver()
{
	m_select_up = sf::Keyboard::W;
	m_select_down = sf::Keyboard::S;
	m_select_enter = sf::Keyboard::Space;

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

	}
}

void GameOver::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	for (int i = 0; i < Menu::getSelections()->size(); i++)
	{
		target.draw(Menu::getSelections()->at(i), states);
	}
}
