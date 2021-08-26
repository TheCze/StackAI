#pragma once
#include "Pos2D.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Randomizer.h"
#include "NavRecConnection.h"
#include <unordered_map>

namespace PathfinderCZ {
	class NavRec {
	public:
		typedef std::shared_ptr<NavRec> nav_ptr;
		NavRec(Pos2D a, Pos2D b) : start(a), size(b) {  }
		Pos2D start;
		Pos2D size;
		bool IsValid() { return size.x > 0 && size.y > 0; }
		bool contains(Pos2D pos);
		void AddConnection(std::shared_ptr<NavRecConnection> neighbor);
		void DepthSearchConnections(float connectioncost, int target);
		Pos2D GetCornerTopLeft();
		Pos2D GetCornerTopRight();
		Pos2D GetCornerBottomLeft();
		Pos2D GetCornerBottomRight();
		std::vector<std::shared_ptr<NavRecConnection>> neighbors;
		float GetHeuristicTo(int navrechash);
		void SetHeuristicTo(int target, float value);
		void ClearHeuristics();
		void PrintHeuristics();
	private:
		std::unordered_map<int, float> heuristics;
	};
}