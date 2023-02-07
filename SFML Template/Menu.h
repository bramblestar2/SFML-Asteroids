#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

//An abstract menu class
class Menu
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;

	int getSelected() const;

protected:
	void setFonts(sf::Font* font);
	void setSelectedSize(const float size);
	void setDefaultSize(const float size);
	void setSelected(const int selection);
	void setDefaultColor(const sf::Color color);
	void setSelectedColor(const sf::Color color);

	void centerText(const sf::Vector2f render_size);
	void updateText();
private:

	float m_default_size, m_selected_size;
	int m_current_selection;
	sf::Color m_default_color, m_selected_color;
	sf::Font m_font;
	std::vector<sf::Text> m_selections;
};

