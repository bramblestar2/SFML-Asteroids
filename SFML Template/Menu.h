#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <exception>

//An abstract menu class
class Menu
{
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates& states) = 0;
	virtual void update() = 0;
	virtual void updateEvents(sf::Event& event) = 0;

	int getSelected() const;

protected:
	void setFonts(sf::Font font);
	void setSelectedSize(const float size);
	void setDefaultSize(const float size);
	bool setSelected(const int selection);
	void setDefaultColor(const sf::Color color);
	void setSelectedColor(const sf::Color color);
	void setTextDistance(const float distance);

	void addSelection(const sf::Text text);
	void addSelection(const std::string text);
	void addNonSelectable(const int index);

	void centerText(const sf::Vector2f render_size);
	void updateText();

	std::vector<int>* getNonSelectables();
	std::vector<sf::Text>* getSelections();
private:

	float m_text_distance;
	float m_default_size, m_selected_size;
	int m_current_selection;
	sf::Color m_default_color, m_selected_color;
	sf::Font m_font;
	std::vector<int> m_non_selectables;
	std::vector<sf::Text> m_selections;
};

