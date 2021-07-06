#pragma once
#include "ASCIISymbol.h"
#include "Randomizer.h"
#include "Spritesheet.h"

void ASCIISymbol::RandomizeShade(int intensity)
{
	int random = random::getInt(intensity);
	sf::Uint8 r = color_.r - random;
	sf::Uint8 g = color_.g - random;
	sf::Uint8 b = color_.b - random;
	color_ = sf::Color(ClampColors(r), ClampColors(g), ClampColors(b), 255);
}

void ASCIISymbol::Draw(sf::RenderWindow& window, Spritesheet& font, float x, float y)
{
	if (bgcolor_ != sf::Color::Transparent) {
		Sprite& bgsprite = font.GetSprite(bgtilecode_);
		bgsprite.setColor(GetBGColor());
		bgsprite.setPosition(x * settings::TILE_WIDTH, y * settings::TILE_WIDTH);
		window.draw(bgsprite);
	}

	Sprite sprite = font.GetSprite(tilecode_);
	sprite.setColor(GetColor());
	sprite.setPosition(x * settings::TILE_WIDTH, y * settings::TILE_WIDTH);
	window.draw(sprite);
}

sf::Uint8 ASCIISymbol::ClampColors(sf::Uint8 x)
{
	if (x < 0)
		return 0;
	if (x > 255)
		return 255;
	return x;
}