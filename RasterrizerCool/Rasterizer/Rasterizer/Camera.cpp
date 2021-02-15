#define _USE_MATH_DEFINES

#include "Camera.h"
#include <iostream>
#include <algorithm>
#include <math.h>

Camera::Camera(float planeDistance, int renderWidth, int renderHeight, glm::mat4 transform)
	: m_planeDistance(planeDistance), m_transform(transform)
{
	this->SetRenderResolution(renderWidth, renderHeight);
}

void Camera::Render(std::vector<Line*> lines, Texture &texture)
{

	for (auto &line : lines)
	{
		line->Render(&texture);
	}


	texture.SetNeedsUpdate();
}

void Camera::SetRenderResolution(int width, int height)
{
	m_renderHeight = height;
	m_renderWidth = width;
	m_totalPixelsToRender = m_renderHeight * m_renderWidth;
	assert(width >= height);
	m_aspectRatio = width / (float)height;
}


