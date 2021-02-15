#pragma once

#include <glm/vec4.hpp>
#include <vector>


class Color
{
public:
	Color();
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);
	Color(glm::vec4 vec);
	Color& operator+=(const Color& rhs)
	{
		this->Set(m_Color + rhs.m_Color);
		return *this;

	}
	friend Color operator+(Color lhs, const Color& rhs)
	{
		lhs += rhs;
		return lhs;
	}
	Color& operator-=(const Color& rhs)
	{
		
		this->Set(m_Color - rhs.m_Color);
		return *this;
	}
	friend Color operator-(Color lhs, const Color& rhs)
	{

		lhs -= rhs;
		return lhs;
	}
	Color& operator/=( float x)
	{
		this->Set(m_Color / x);
		return *this;

	}
	friend Color operator/(Color lhs, float x)
	{

		lhs /= x;
		return lhs;
	}
	Color& operator*=(float x)
	{
		this->Set(m_Color * x);
		return *this;

	}
	friend Color operator*(Color lhs, float x)
	{

		lhs *= x;
		return lhs;
	}
	glm::vec4 Get();
	std::vector<unsigned int> GetSdlTextureFomatted();
	void Set(glm::vec4 newColor);

private:
	glm::vec4 m_Color;	// r, g, b, a
};