#pragma once
struct Pos2D {
	Pos2D(int a, int b): x(a), y(b) {}
	Pos2D(){}
	int x = 0;
	int y = 0;
	inline bool operator==(const Pos2D& b) { return x == b.x && y == b.y; }
	Pos2D operator+(const Pos2D& b) { return Pos2D(x + b.x, y + b.y); }
	inline bool operator!=(const Pos2D& b) { return x != b.x || y != b.y; }
	Pos2D Adjacent(int px, int py) { return Pos2D(x + px, y + py); }
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