#pragma once
#include <memory>
#include "NavRec.h"
#include <set>
#include "Pos2D.h"

class World;
namespace PathfinderCZ {
	typedef std::shared_ptr<NavRec> nav_ptr;
	class NavRecSystem {
	public:
		void CheckNavRecHeuristics(nav_ptr& target_nav_rec);
		void ClearNavRecHeuristic();
		nav_ptr GetNavRecAtPos(Pos2D position);
		nav_ptr UpdateNavRecIfChanged(nav_ptr& navrec, Pos2D position);
		const void UpdateNavRec(World& world, Pos2D location);
	private:
		bool HasThisNavRecBeenCalculated(int target);
		void UpdateNavRecConnections(World& world);
		void FindNavRecsOnLine(nav_ptr navrec, Pos2D start, Pos2D target);
		void AddNavConnectionAtPos(const Pos2D& start, nav_ptr& navrec);
		const bool IsInNavRec(Pos2D location);
		const nav_ptr CreateNavRecFromPos(World& world, Pos2D location);
		std::set<int> searched_navrecs;
		std::vector<nav_ptr> navrecs;
	};
}
