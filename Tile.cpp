#pragma once
#include "Tile.h"
#include "Randomizer.h"

void Tile::walk_on()
{
	usage+=0.02f;
	if (usage > 1)
		usage = 1;
	updateColors();
}

void Tile::renaturalize() {
	usage -= 0.5f;
	if (usage < 0)
		usage = 0;
	updateColors();
}

void Tile::updateColors()
{
	float r_dif = defaultColor.r - usageColor.r;
	float g_dif = defaultColor.g - usageColor.g;
	float b_dif = defaultColor.b - usageColor.b;
	float a_dif = defaultColor.a - usageColor.a;
	m_symbol.getBGColor().r = defaultColor.r - (r_dif * usage);
	m_symbol.getBGColor().g = defaultColor.g - (g_dif * usage);
	m_symbol.getBGColor().b = defaultColor.b - (b_dif * usage);
	m_symbol.getBGColor().a = defaultColor.a - (a_dif * usage);
}

float Tile::GetTileCost()
{
	return tile_cost*(1-usage*tileCostUsageMod);
}
