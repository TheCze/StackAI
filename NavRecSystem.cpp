#include "NavRecSystem.h"
#include "World.h"

namespace PathfinderCZ {
	void NavRecSystem::CheckNavRecHeuristics(nav_ptr& target_nav_rec) {
		if (!HasThisNavRecBeenCalculated(target_nav_rec->start.hash())) {
			target_nav_rec->DepthSearchConnections(0, target_nav_rec->start.hash());
			searched_navrecs.insert(target_nav_rec->start.hash());
		}
	}
	void NavRecSystem::ClearNavRecHeuristic()
	{
		searched_navrecs.clear();
		navrecs.clear();
	}
	nav_ptr NavRecSystem::GetNavRecAtPos(Pos2D position)
	{
		for (auto navrec : navrecs) {
			if (navrec->contains(position)) {
				return navrec;
			}
		}
		return nullptr;
	}
	bool NavRecSystem::HasThisNavRecBeenCalculated(int target)
	{
		return searched_navrecs.find(target) != searched_navrecs.end();
	}

	const void NavRecSystem::UpdateNavRec(World& world, Pos2D location) {
		ClearNavRecHeuristic();
		int width = world.kTilesWidth - location.x;
		int height = world.kTilesHeight - location.y;
		for (int y = location.y; y < height; y++) {
			for (int x = location.x; x < width; x++) {
				if (world.GetTile(x, y).walkable_) {
					if (!IsInNavRec(Pos2D(x, y))) {
						auto navrec = CreateNavRecFromPos(world, Pos2D(x, y));
						if (navrec->IsValid()) {
							navrecs.push_back(navrec);
						}
						else
							std::cout << "Invalid";
					}
				}
			}
		}
		UpdateNavRecConnections(world);
	}

	//Search adjacent to each navrec in all four directions for other Navrecs
	void NavRecSystem::UpdateNavRecConnections(World& world)
	{
		for (auto& navrec : navrecs) {
			Pos2D start = navrec->GetCornerTopLeft();
			Pos2D target = navrec->GetCornerTopRight();
			start.y -= 1;
			target.y -= 1;
			if (world.IsValid(start) && world.IsValid(target))
				FindNavRecsOnLine(navrec, start, target);
			start = navrec->GetCornerTopLeft();
			target = navrec->GetCornerBottomLeft();
			start.x -= 1;
			target.x -= 1;
			if (world.IsValid(start) && world.IsValid(target))
				FindNavRecsOnLine(navrec, start, target);
			start = navrec->GetCornerTopRight();
			target = navrec->GetCornerBottomRight();
			start.x += 1;
			target.x += 1;
			if (world.IsValid(start) && world.IsValid(target))
				FindNavRecsOnLine(navrec, start, target);
			start = navrec->GetCornerBottomLeft();
			target = navrec->GetCornerBottomRight();
			start.y += 1;
			target.y += 1;
			if (world.IsValid(start) && world.IsValid(target))
				FindNavRecsOnLine(navrec, start, target);
		}
	}

	//Search for a navrec between two Pos2Ds and add a connection to a given navrec
	void NavRecSystem::FindNavRecsOnLine(nav_ptr navrec, Pos2D start, Pos2D target) {
		while (start != target) {
			AddNavConnectionAtPos(start, navrec);
			start.MoveTowards(target);
		}
		AddNavConnectionAtPos(target, navrec);
	}

	void NavRecSystem::AddNavConnectionAtPos(const Pos2D& start, nav_ptr& navrec)
	{
		nav_ptr neighbor = GetNavRecAtPos(start);
		if (neighbor != nullptr) {
			std::shared_ptr<NavRecConnection> conn(new NavRecConnection(navrec, neighbor));
			navrec->AddConnection(conn);
		}
	}

	const bool NavRecSystem::IsInNavRec(Pos2D location) {
		for (auto navrec : navrecs) {
			if (navrec->contains(location)) {
				return true;
			}
		}
		return false;
	}

	const nav_ptr NavRecSystem::CreateNavRecFromPos(World& world, Pos2D location) {
		int width = world.kTilesWidth;
		int height = world.kTilesHeight;
		for (int x = location.x; x < width; x++) {
			if (!world.GetTile(x, location.y).walkable_ || IsInNavRec(Pos2D(x, location.y))) {
				width = x;
				break;
			}
		}
		for (int y = location.y; y < height; y++) {
			for (int x = location.x; x < width; x++) {
				if (!world.GetTile(x, y).walkable_ || IsInNavRec(Pos2D(x, y))) {
					height = y;
					break;
				}
			}
		}
		height -= location.y;
		width -= location.x;
		Pos2D size(width, height);
		nav_ptr nav(new NavRec(location, size));
		return nav;
	}

	nav_ptr NavRecSystem::UpdateNavRecIfChanged(nav_ptr& navrec, Pos2D position) {
		if (navrec->contains(position))
			return navrec;
		else
			return GetNavRecAtPos(position);
	}
}