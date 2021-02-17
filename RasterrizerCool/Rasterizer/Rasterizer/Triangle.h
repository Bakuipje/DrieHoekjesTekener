#pragma once
#include <glm/glm.hpp>
#include "Color.h"
#include "Texture.h"
#include "Line.h"
class Triangle
{
public:
	Triangle() {}
	Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2);
	~Triangle();
	void Render(Texture* texture);
	void RenderLine(Texture* texture);
private:
	
	Line *m_edge0;
	Line *m_edge1;
	Line *m_edge2;
	glm::vec3 m_v0, m_v1, m_v2;
};

