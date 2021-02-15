#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include "Line.h"



class Camera
{
public:
	Camera() : m_planeDistance(0), m_renderWidth(0), m_renderHeight(0), m_transform(glm::mat4())
	{}
	Camera(float planeDistance, int renderWidth, int renderHeight, glm::mat4 transform);
	//void Render(Texture &texture);
	void Render(std::vector<Line*> lines, Texture &texture);
	void SetRenderResolution(int width, int height);


private:
	float m_planeDistance;

	float fov = 90;

	int m_renderWidth;
	int m_renderHeight;
	int m_totalPixelsToRender;
	float m_aspectRatio;

	glm::mat4 m_transform;
	//std::vector<Ray> m_rays;
};

