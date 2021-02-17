#pragma once

#include <glm/glm.hpp>
#include <vector>

std::vector<glm::vec2> interpolate(int x0, int y0, int x1, int y1)
{
	std::vector<glm::vec2> returnVector;
	if (x0 == x1)
	{
		returnVector.push_back(glm::vec2(x0, y0));
		return returnVector;
	}
	float a = (float)(y1-y0) / (float)(x1-x0);
	float y = y0;

	for (int i = 0; i < (x1 - x0); i++)
	{
		returnVector.push_back(glm::vec2(x0 + i, y));
		y += a;
	}
	return returnVector;


}