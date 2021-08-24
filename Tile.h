#pragma once
#include <SFML/Graphics.hpp>
#include "ASCIISymbol.h"
#include "Pos2D.h"
class Tile {
public:
	ASCIISymbol symbol_ = ASCIISymbol();
	Tile() {}
	Tile(ASCIISymbol symbol) : symbol_(symbol) {}
	Tile(ASCIISymbol symbol, Pos2D pos) : symbol_(symbol), pos_(pos) {}
	bool walkable_ = true;
	Pos2D pos_ = Pos2D();
	sf::Color defaultColor_;
	sf::Color usageColor_;
	float tilecost_usage_mod = 0.5f;
	float GetTileCost();
	void WalkOn();
	void Renaturalize();
	void UpdateColors();
	void SetDefaultTileCost(float cost) { tile_cost_ = cost; }
private:
	float usage_ = 0.0f;
	float tile_cost_ = 1;
};