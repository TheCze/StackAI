#pragma once
#include <SFML/Graphics.hpp>
#include "Spritesheet.h"
#include "ASCII.h"
#include "Pos2D.h"
struct ASCIISymbol {
	ASCIISymbol() : tilecode_(0), color_(sf::Color::White) {  }
	ASCIISymbol(int tilecode) : tilecode_(tilecode), color_(sf::Color::White) {  }
	ASCIISymbol(int tilecode, sf::Color color): tilecode_(tilecode), color_(color){  }
	int GetTileCode() { return tilecode_; }
	void SetTileCode(int tilecode) { tilecode_ = tilecode; }
	sf::Color& GetColor() { return color_; }
	sf::Color& GetBGColor() { return bgcolor_; }
	void SetColor(sf::Color c) { color_ = c; }
	void SetBGColor(sf::Color c) { bgcolor_ = c; }
	void RandomizeShade(int intensity);
	void Draw(sf::RenderWindow& window, Spritesheet& font, float x, float y);
	void Draw(sf::RenderWindow& window, Spritesheet& font, Pos2D pos, Pos2D scale);
private:
	int tilecode_=0;
	int bgtilecode_ = ASCII::block_full;
	sf::Color bgcolor_ = sf::Color::Transparent;
	sf::Color color_=sf::Color::White;
	sf::Uint8 ClampColors(sf::Uint8 x);
	
};