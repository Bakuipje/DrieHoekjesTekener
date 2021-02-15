#include "Color.h"
#include <glm/glm.hpp> 

Color::Color()
{
	m_Color = glm::vec4(0, 0, 0, 1.f);
	this->Set(m_Color);
}


Color::Color(float r, float g, float b)
{
	m_Color = glm::vec4(r, g, b, 1.f);
	this->Set(m_Color);
}

Color::Color(float r, float g, float b, float a)
{
	m_Color = glm::vec4(r, g, b, a);
	this->Set(m_Color);
}

Color::Color(glm::vec4 vec)
{
	this->Set(vec);
}

glm::vec4 Color::Get()
{
	return m_Color;
}

void Color::Set(glm::vec4 newColor)
{
	m_Color.x = glm::clamp(newColor.x, 0.f, 1.f);
	m_Color.y = glm::clamp(newColor.y, 0.f, 1.f);
	m_Color.z = glm::clamp(newColor.z, 0.f, 1.f);
	m_Color.w = glm::clamp(newColor.w, 0.f, 1.f);
}
