#pragma once
#include "Pos2D.h"
#include <memory>

namespace PathfinderCZ {
	struct Pathnode {
		typedef std::shared_ptr<Pathnode> node_ptr;
		Pathnode(Pos2D start) : pos(start) {}
		Pos2D pos;
		node_ptr next;
		float weight = 1;
		bool IsLast() { return !next.get(); }
		int length(int i)
		{
			i++;
			if (next)
				return next->length(i);
			else
				return i;
		}
	};
}