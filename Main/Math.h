#pragma once

#include <cmath>

class Point
{
public:
	float x, y;
private:

};

static float distance(Point p1, Point p2)
{
	return sqrtf(
		powf(p2.x - p1.x, 2.0f)
		+
		powf(p2.y - p1.y, 2.0f)
	);
}