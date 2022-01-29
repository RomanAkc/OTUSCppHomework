#include "additional_func.h"

int fact(int p) {
	if (p == 0)
		return 1;

	return p * fact(p - 1);
}
