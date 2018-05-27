#pragma once

#include "resource.h"

struct rcCoords
{
	int x1, y1, x2, y2;

	rcCoords()
	{
		x1 = y1 = 10;
		x2 = y2 = 100;
	}

	rcCoords(int _x1, int _y1, int _x2, int _y2)
	{
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
	}
};
