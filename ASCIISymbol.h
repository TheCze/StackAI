#pragma once
#include <SFML/Graphics.hpp>
#include "Spritesheet.h"
#include "ASCII.h"
struct ASCIISymbol {
	ASCIISymbol() : m_tilecode(0), m_color(sf::Color::White) {  }
	ASCIISymbol(int tilecode) : m_tilecode(tilecode), m_color(sf::Color::White) {  }
	ASCIISymbol(int tilecode, sf::Color color): m_tilecode(tilecode), m_color(color){  }
	int getTileCode() { return m_tilecode; }
	void setTileCode(int tilecode) {  }
	sf::Color& getColor() { return m_color; }
	sf::Color& getBGColor() { return m_bgcolor; }
	void setColor(sf::Color c) { m_color = c; }
	void setBGColor(sf::Color c) { m_bgcolor = c; }
	void randomize_shade(int intensity);
	void draw(sf::RenderWindow& window, Spritesheet& font, float x, float y);
private:
	int m_tilecode=0;
	int m_bgtilecode = ASCII::block_full;
	sf::Color m_bgcolor = sf::Color::Transparent;
	sf::Color m_color=sf::Color::White;
	sf::Uint8 clamp_colors(sf::Uint8 x);
	
};