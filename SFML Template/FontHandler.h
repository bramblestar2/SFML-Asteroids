#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class FontHandler
{
public:
	~FontHandler();

	static void loadFont(const std::string font_id, const std::string font_path);
	static sf::Font* getFont(const std::string font_id);
	static void removeFont(const std::string font_id);
private:
	static std::map<std::string, sf::Font*> m_fonts;
};

