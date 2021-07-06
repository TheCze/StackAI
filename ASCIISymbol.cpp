#pragma once
#include "ASCIISymbol.h"
#include "Randomizer.h"
#include "Spritesheet.h"

void ASCIISymbol::randomize_shade(int intensity)
{
	int random = random::getInt(intensity);
	sf::Uint8 r = m_color.r - random;
	sf::Uint8 g = m_color.g - random;
	sf::Uint8 b = m_color.b - random;
	m_color = sf::Color(clamp_colors(r), clamp_colors(g), clamp_colors(b), 255);
}

void ASCIISymbol::draw(sf::RenderWindow& window, Spritesheet& font, float x, float y)
{
	if (m_bgcolor != sf::Color::Transparent) {
		Sprite& bgsprite = font.GetSprite(m_bgtilecode);
		bgsprite.setColor(getBGColor());
		bgsprite.setPosition(x * settings::TILE_WIDTH, y * settings::TILE_WIDTH);
		window.draw(bgsprite);
	}

	Sprite sprite = font.GetSprite(m_tilecode);
	sprite.setColor(getColor());
	sprite.setPosition(x * settings::TILE_WIDTH, y * settings::TILE_WIDTH);
	window.draw(sprite);
}

sf::Uint8 ASCIISymbol::clamp_colors(sf::Uint8 x)
{
	if (x < 0)
		return 0;
	if (x > 255)
		return 255;
	return x;
}