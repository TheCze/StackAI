#pragma once
#include <cstdlib>
#include <time.h>
namespace random {
	static bool r_init = false;
	static void init() {
		if (!r_init) {
			srand(static_cast <unsigned> (time(0)));
			r_init = true;
		}
	}

	static float getFloat(float LO=0, float HI=1) {
		init();
		return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
	}
	static int getInt(int HI) {
		init();
		if (HI == 0)
			return 0;
		return rand() % (HI+1);
	}

	static bool getBool() {
		init();
		return rand() % 2;
	}
}