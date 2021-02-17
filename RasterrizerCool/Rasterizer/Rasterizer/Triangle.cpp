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
{
	// ensure m_v0 is the highest point
	if (m_v1.y < m_v0.y)
		std::swap(m_v1, m_v0);
	if (m_v2.y < m_v0.y)
		std::swap(m_v2, m_v0);
	// swap v1 and v2 to ensure v2 is the lowest point
	if (m_v2.y < m_v1.y)
		std::swap(m_v2, m_v1);
	// generate edge coordinates
	std::vector<glm::vec2> edge01, edge02, edge12;
	edge01 = interpolate(m_v0.y, m_v0.x, m_v1.y, m_v1.x);
	edge02 = interpolate(m_v0.y, m_v0.x, m_v2.y, m_v2.x);
	edge12 = interpolate(m_v1.y, m_v1.x, m_v2.y, m_v2.x);

	// because we ordered the points the distance between v0.y-> v2.y is the same as the distance between v0.y ->v1.y ->v2.y
	std::vector<glm::vec2>edge012( edge01);
	std::copy(edge12.begin(), edge12.end(), std::back_inserter(edge012));

	int midlepoint = edge012.size() / 2;
	std::vector<glm::vec2> leftEdge, rightEdge;
	// check which edge is left and right (interpolate function returns coordinates flipped)
	if (edge02[midlepoint].y < edge012[midlepoint].y)
	{
		leftEdge = edge02;
		rightEdge = edge012;
	}
	else {
		leftEdge = edge012;
		rightEdge = edge02;
	}
	for (int i = 0; i < leftEdge.size(); i++)
	{
		for (int x = leftEdge[i].y; x < rightEdge[i].y; x++)
		{
			texture->SetPixel(x, leftEdge[i].x, Color(1,0,0));
		}
	}

}
void Triangle::RenderLine(Texture* texture)
{
	m_edge0->Render(texture);
	m_edge1->Render(texture);
	m_edge2->Render(texture);

}