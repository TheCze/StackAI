#pragma once
#include "Pos2D.h"
#include <memory>
#include "Pathnode.h"
typedef std::shared_ptr<Pathnode> node_ptr;
struct Path {
	node_ptr first;
	node_ptr last;
	Path(node_ptr start) { first = start; last = start;}
	Path(Pos2D start_pos) { node_ptr start (new Pathnode(start_pos)); first = start; last = start; }
	void addNode(Pos2D pos) { node_ptr ptr(new Pathnode(pos)); last->next = ptr; last = ptr; }
	node_ptr get_next() { progress(); return first; }
	bool reached_end() { return first == last; }
	void progress() { if(!reached_end()) first = first->next; }
	void reverse();
	int length();
};