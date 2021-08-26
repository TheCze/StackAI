#pragma once
#include "Pos2D.h"
#include <memory>
#include "Pathnode.h"

namespace PathfinderCZ {
	typedef std::shared_ptr<Pathnode> node_ptr;
	struct Path {
		node_ptr first;
		node_ptr last;
		Path(node_ptr start) { first = start; last = start; }
		Path(Pos2D start_pos) { node_ptr start(new Pathnode(start_pos)); first = start; last = start; }
		void AddNode(Pos2D pos) { node_ptr ptr(new Pathnode(pos)); last->next = ptr; last = ptr; }
		bool HasReachedEnd() { return first == last; }
		node_ptr GetNext() { Progress(); return first; }
		void ReversePath();
		int length();
	private:
		void Progress() { if (!HasReachedEnd()) first = first->next; }
	};
}