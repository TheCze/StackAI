#pragma once
namespace CzeUtils {
	static const int GetCantor(int x, int y) {
		return (x + y) * (x + y + 1) / 2 + y;
	}
}