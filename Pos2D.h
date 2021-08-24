#pragma once
#include <ostream>

struct Pos2D {
	Pos2D(int a, int b): x(a), y(b) {}
	Pos2D(){}
	int x = 0;
	int y = 0;
	int saved_hash = -1;
	inline bool operator==(const Pos2D& b) { return x == b.x && y == b.y; }
	Pos2D operator+(const Pos2D& b) { return Pos2D(x + b.x, y + b.y); }
	inline bool operator!=(const Pos2D& b) { return x != b.x || y != b.y; }
	Pos2D Adjacent(int px, int py) { return Pos2D(x + px, y + py); }
	int hash() {
		if(saved_hash == -1)
			saved_hash = ((x + y) * (x + y + 1) / 2 + y);
		return saved_hash;
	}
	void MoveTowards(Pos2D target){
		if (x > target.x)
			x--;
		else if (x < target.x)
			x++;
		else if (y > target.y)
			y--;
		else if (y < target.y)
			y++;
	}
};

std::ostream& operator<<(std::ostream& os, const Pos2D& pos);

