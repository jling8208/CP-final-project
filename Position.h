#pragma once

#include <iostream>

struct position
{
	position(): x(0.0f), y(0.0f) {}
	position(float p_x, float p_y): x(p_x), y(p_y) {}

	void print()
	{
		std::cout << "Position at (" << x << ", " << y << ")" << std::endl;
	}

	float x, y;
};
