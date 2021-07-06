#pragma once
#include <SFML/Graphics.hpp>
#include "ASCIISymbol.h"
#include "Pos2D.h"
class Tile {
public:
	ASCIISymbol m_symbol = ASCIISymbol();
	Tile() {}
	Tile(ASCIISymbol symbol) : m_symbol(symbol) {}
	Tile(ASCIISymbol symbol, Pos2D pos) : m_symbol(symbol), m_pos(pos) {}
	bool walkable = true;
	Pos2D m_pos = Pos2D();
	void walk_on();
	void renaturalize();
	void updateColors();
	void SetDefaultTileCost(float cost) { tile_cost = cost; }
	sf::Color defaultColor;
	sf::Color usageColor;
	float tileCostUsageMod = 0.5f;
	float GetTileCost();
private:
	float usage = 0.0f;
	float tile_cost = 1;

};