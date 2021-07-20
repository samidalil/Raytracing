#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

#include "../headers/math/Point.h"
#include "../headers/math/Vector.h"
#include "../headers/math/Matrix.h"

void unit() {
	assertm(true, "Ne doit pas être levée");

	Point p;

	//assertm();
}