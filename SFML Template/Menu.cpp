#include "Menu.h"

int Menu::getSelected() const
{
    return m_current_selection;
}

void Menu::setFonts(sf::Font* font)
{
    for (int i = 0; i < m_selections.size(); i++)
    {
        m_selections.at(i).setFont(*font);
    }
}

void Menu::setSelectedSize(const float size)
{
    m_selected_size = size;
}

void Menu::setDefaultSize(const float size)
{
    m_default_size = size;
}

void Menu::setSelected(const int selection)
{
    m_current_selection = selection;
}

void Menu::setDefaultColor(const sf::Color color)
{
    m_default_color = color;
}

void Menu::setSelectedColor(const sf::Color color)
{
    m_selected_color = color;
}

void Menu::centerText(const sf::Vector2f render_size)
{
    int selection_count = m_selections.size();
    int height_difference = 0;
    if (selection_count > 0)
        height_difference = m_selections.at(0).getGlobalBounds().height;
}

void Menu::updateText()
{
}
