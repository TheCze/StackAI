#pragma once
#include "Pos2D.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Randomizer.h"
#include "NavRecConnection.h"
struct NavRec {
	typedef std::shared_ptr<NavRec> nav_ptr;
	NavRec(Pos2D a, Pos2D b) : start(a), size(b) {  }
	Pos2D start;
	Pos2D size;
	float current_heuristic = -1;
	bool IsValid() { return size.x > 0 && size.y > 0; }
	bool contains(Pos2D pos);
	void AddConnection(std::shared_ptr<NavRecConnection> neighbor);
	void DepthSearchConnections(float connectioncost);
	Pos2D GetCornerTopLeft();
	Pos2D GetCornerTopRight();
	Pos2D GetCornerBottomLeft();
	Pos2D GetCornerBottomRight();
	std::vector<std::shared_ptr<NavRecConnection>> neighbors;
private:
};