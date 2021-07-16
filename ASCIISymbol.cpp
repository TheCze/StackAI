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
	Draw(window, font, Pos2D(x,y), Pos2D(1,1));
}

void ASCIISymbol::Draw(sf::RenderWindow& window, Spritesheet& font, Pos2D pos, Pos2D scale)
{
	if (bgcolor_ != sf::Color::Transparent) {
		Sprite& bgsprite = font.GetSprite(bgtilecode_);
		bgsprite.setColor(GetBGColor());
		bgsprite.setPosition(pos.x * settings::TILE_WIDTH, pos.y * settings::TILE_WIDTH);
		window.draw(bgsprite);
	}

	Sprite sprite = font.GetSprite(tilecode_);
	sprite.setColor(GetColor());
	sprite.setPosition(pos.x * settings::TILE_WIDTH, pos.y * settings::TILE_WIDTH);
	sprite.setScale(sf::Vector2f(scale.x, scale.y));
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