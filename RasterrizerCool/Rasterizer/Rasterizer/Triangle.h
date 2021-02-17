#pragma once
#include <glm/glm.hpp>
#include "Color.h"

class Triangle
{
public:
	Triangle() {}
	Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2) :
		m_v0(vertex0), m_v1(vertex1), m_v2(vertex2) {}
	void Render(Texture* texture);
	void RenderLine(Texture* texture);
private:
	glm::vec3 m_v0, m_v1, m_v2;
};

