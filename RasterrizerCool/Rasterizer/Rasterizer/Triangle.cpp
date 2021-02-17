#include "Common.h"
#include "Line.h"
#include "Triangle.h"

Triangle::Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2) :
	m_v0(vertex0), m_v1(vertex1), m_v2(vertex2) 
{
	m_edge0 = new Line(vertex0, vertex1, Color(1, 1, 1), Color(1, 1, 1));
	m_edge1 = new Line(vertex1, vertex2, Color(1, 1, 1), Color(1, 1, 1));
	m_edge2 = new Line(vertex2, vertex0, Color(1, 1, 1), Color(1, 1, 1));
}
Triangle::~Triangle()
{
	delete m_edge0, m_edge1, m_edge2;
}
void Triangle::Render(Texture* texture)
{}
void Triangle::RenderLine(Texture* texture)
{
	m_edge0->Render(texture);
	m_edge1->Render(texture);
	m_edge2->Render(texture);

}