#include "Menu.h"
#include <iostream>

int Menu::getSelected() const
{
    return m_current_selection;
}

void Menu::setFonts(sf::Font font)
{
    for (int i = 0; i < m_selections.size(); i++)
    {
        m_selections.at(i).setFont(font);
    }
    
    m_font = font;
}

void Menu::setSelectedSize(const float size)
{
    m_selected_size = size;
}

void Menu::setDefaultSize(const float size)
{
    m_default_size = size;
}

bool Menu::setSelected(const int selection)
{
    //std::cout << selection << std::endl;

    if (selection < 0 || selection >= m_selections.size())
    {
        throw std::out_of_range("(Menu Class) setSelected(const int): "
                "Index out of range {" + std::to_string(selection) + "}");
        return false;
    }

    for (int i = 0; i < m_non_selectables.size(); i++)
        if (selection == m_non_selectables.at(i))
        {
            //std::cout << "(Menu Class) setSelected(const int): "
            //    "selection cannot be set. It's part of non selectables.\n";
            return false;
        }

    m_current_selection = selection;
    return true;
}

void Menu::setDefaultColor(const sf::Color color)
{
    m_default_color = color;

    for (int i = 0; i < m_selections.size(); i++)
        if (i != m_current_selection)
            m_selections.at(i).setFillColor(m_default_color);
}

void Menu::setSelectedColor(const sf::Color color)
{
    m_selected_color = color;

    for (int i = 0; i < m_selections.size(); i++)
        if (i == m_current_selection)
            m_selections.at(i).setFillColor(m_selected_color);
}

void Menu::addSelection(const sf::Text text)
{
    m_selections.push_back(text);
}

void Menu::addNonSelectable(const int index)
{
    if (index < 0 || index >= m_selections.size())
    {
        throw std::out_of_range("(Menu Class) addNonSelectable(): Index out of range");
        return;
    }

    m_non_selectables.push_back(index);
}

void Menu::centerText(const sf::Vector2f render_size)
{
    int selection_count = m_selections.size();
    int height_difference = 0;
    if (selection_count > 0)
    {
        height_difference = m_selections.at(0).getGlobalBounds().height * 2;

        for (int i = 0; i < selection_count; i++)
        {
            //Set the origin of selections[i] to the center
            float width, height;
            width = m_selections.at(i).getGlobalBounds().width;
            height = m_selections.at(i).getGlobalBounds().height;
            m_selections.at(i).setOrigin(width/2, height/2);

            /* <What it would look like>
            *  
            *           MENU
            *           PLAY
            *           QUIT
            * 
            */

            float xpos = (render_size.x/2);
            float ypos = (render_size.y / selection_count) + (i*height_difference);

            m_selections.at(i).setPosition(xpos, ypos);
        }
    }


}

void Menu::updateText()
{
    for (int i = 0; i < m_selections.size(); i++)
    {
        //Set sizes, colors, and fonts
        m_selections.at(i).setFont(m_font);

        if (i != m_current_selection)
        {
            m_selections.at(i).setCharacterSize(m_default_size);
            m_selections.at(i).setFillColor(m_default_color);
        }
        else
        {
            m_selections.at(i).setCharacterSize(m_selected_size);
            m_selections.at(i).setFillColor(m_selected_color);
        }

        float width, height;
        width = m_selections.at(i).getGlobalBounds().width;
        height = m_selections.at(i).getGlobalBounds().height;
        m_selections.at(i).setOrigin(width / 2, height / 2);
    }
}

std::vector<int>* Menu::getNonSelectables()
{
    return &m_non_selectables;
}

std::vector<sf::Text>* Menu::getSelections()
{
    return &m_selections;
}
