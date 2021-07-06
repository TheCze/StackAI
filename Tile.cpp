#pragma once
#include "Tile.h"
#include "Randomizer.h"

void Tile::WalkOn()
{
	usage_+=0.02f;
	if (usage_ > 1)
		usage_ = 1;
	UpdateColors();
}

void Tile::Renaturalize() {
	usage_ -= 0.5f;
	if (usage_ < 0)
		usage_ = 0;
	UpdateColors();
}

void Tile::UpdateColors()
{
	float r_dif = defaultColor_.r - usageColor_.r;
	float g_dif = defaultColor_.g - usageColor_.g;
	float b_dif = defaultColor_.b - usageColor_.b;
	float a_dif = defaultColor_.a - usageColor_.a;
	symbol_.getBGColor().r = defaultColor_.r - (r_dif * usage_);
	symbol_.getBGColor().g = defaultColor_.g - (g_dif * usage_);
	symbol_.getBGColor().b = defaultColor_.b - (b_dif * usage_);
	symbol_.getBGColor().a = defaultColor_.a - (a_dif * usage_);
}

float Tile::GetTileCost()
{
	return tile_cost_*(1-usage_*tilecost_usage_mod);
}
