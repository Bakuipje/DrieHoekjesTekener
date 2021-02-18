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
	std::vector<glm::vec2> edgeX01, edgeX02, edgeX12;
	std::vector<glm::vec2> edgeZ01, edgeZ02, edgeZ12;
	edgeX01 = interpolate(m_v0.y, m_v0.x, m_v1.y, m_v1.x);
	edgeX02 = interpolate(m_v0.y, m_v0.x, m_v2.y, m_v2.x);
	edgeX12 = interpolate(m_v1.y, m_v1.x, m_v2.y, m_v2.x);

	edgeZ01 = interpolate(m_v0.y, m_v0.z, m_v1.y, m_v1.z);
	edgeZ02 = interpolate(m_v0.y, m_v0.z, m_v2.y, m_v2.z);
	edgeZ12 = interpolate(m_v1.y, m_v1.z, m_v2.y, m_v2.z);

	// because we ordered the points the distance between v0.y-> v2.y is the same as the distance between v0.y ->v1.y ->v2.y
	std::vector<glm::vec2>edgeX012( edgeX01);
	std::copy(edgeX12.begin(), edgeX12.end(), std::back_inserter(edgeX012));

	std::vector<glm::vec2>edgeZ012(edgeZ01);
	std::copy(edgeZ12.begin(), edgeZ12.end(), std::back_inserter(edgeZ012));

	int midlepoint = edgeX012.size() / 2;
	std::vector<glm::vec2> leftEdgeX, rightEdgeX;
	std::vector<glm::vec2> leftEdgeZ, rightEdgeZ;

	// check which edge is left and right (interpolate function returns coordinates flipped)
	if (edgeX02[midlepoint].y < edgeX012[midlepoint].y)
	{
		leftEdgeX = edgeX02;
		rightEdgeX = edgeX012;
		leftEdgeZ = edgeZ02;
		rightEdgeZ = edgeZ012;
	}
	else 
	{
		leftEdgeX = edgeX012;
		rightEdgeX = edgeX02;
		leftEdgeZ = edgeZ012;
		rightEdgeZ = edgeZ02;
	}
	for (int i = 0; i < leftEdgeX.size(); i++)
	{
		for (int x = leftEdgeX[i].y; x < rightEdgeX[i].y; x++)
		{
			glm::vec4 col = glm::vec4(1, 0, 0, 1)*leftEdgeZ[i].y;
			texture->SetPixel(x, leftEdgeX[i].x, col);
		}
	}

}
void Triangle::RenderLine(Texture* texture)
{
	m_edge0->Render(texture);
	m_edge1->Render(texture);
	m_edge2->Render(texture);

}