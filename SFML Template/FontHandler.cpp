#include "FontHandler.h"

std::map<std::string, sf::Font*> FontHandler::m_fonts;

FontHandler::~FontHandler()
{
	for (auto fonts : m_fonts)
	{
		removeFont(fonts.first);
	}
}

void FontHandler::loadFont(const std::string font_id, const std::string font_path)
{
	m_fonts[font_id] = new sf::Font();
	m_fonts[font_id]->loadFromFile(font_path);
}

sf::Font& FontHandler::getFont(const std::string font_id)
{
	return *m_fonts[font_id];
}

void FontHandler::removeFont(const std::string font_id)
{
	delete m_fonts[font_id];
	m_fonts.erase(font_id);
}
