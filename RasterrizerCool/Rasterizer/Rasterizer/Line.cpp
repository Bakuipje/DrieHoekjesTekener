#include "Texture.h"
#include "Line.h"

Line::Line(glm::vec3 a_startPos, glm::vec3 a_endPos, Color a_startColor, Color a_endColor):
	startPos(a_startPos), endPos(a_endPos), startColor(a_startColor), endColor(a_endColor)
{

}

void Line::Render(Texture* texture)
{
	float deltaX = (endPos.x - startPos.x);
	float deltaY = (endPos.y - startPos.y);
	if (abs(deltaX) > abs(deltaY))
	{
		if (startPos.x > endPos.x)
		{
			std::swap(startColor, endColor);
			std::swap(startPos, endPos);
		}
		float a = deltaY / deltaX;
		float y = startPos.y;

		glm::vec4 deltaColor = (startColor.Get() - endColor.Get()) / deltaX;
		for (int i = 0; i < deltaX; i++)
		{
			glm::vec4 test = startColor.Get()-deltaColor*(float)i;
			Color pixelCol = Color( test);
			texture->SetPixel(startPos.x + i, y, pixelCol);
			y += a;
		}
	}
	else
	{
		if (startPos.y > endPos.y)
			std::swap(startPos, endPos);

		float a = deltaX / deltaY;
		float x = startPos.x;

		glm::vec4 deltaColor = (startColor.Get() - endColor.Get()) / deltaX;
		deltaColor = glm::abs(deltaColor);
		for (int i = 0; i < deltaY; i++)
		{
			Color pixelCol = Color(startColor.Get() - (deltaColor*(float)i));
			texture->SetPixel(x, startPos.y +1, pixelCol);
			x += a;
		}
	}

}

void Line::SetStartPos(glm::vec3 pos)
{
	startPos = pos;
}
void Line::SetEndPos(glm::vec3 pos)
{
	endPos = pos;
}
void Line::SetStartColor(Color color)
{
	startColor = color;
}
void Line::SetEndColor(Color color)
{
	endColor = color;
}
// Getter
glm::vec3 Line::GetStartPos()
{
	return startPos;
}
glm::vec3 Line::GetEndPos()
{
	return endPos;
}
Color Line::GetStartColor()
{
	return startColor;
}
Color Line::GetEndColor()
{
	return endColor;
}