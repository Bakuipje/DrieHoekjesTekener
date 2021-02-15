#include "Texture.h"
#include "Line.h"

Line::Line(glm::vec3 a_startPos, glm::vec3 a_endPos, Color a_startColor, Color a_endColor):
	startPos(a_startPos), endPos(a_endPos), startColor(a_startColor), endColor(a_endColor)
{

}
void Line::Render(Texture* texture)
{
	float deltaX = (endPos.x - startPos.x);
	int modifier = 1;
	if (deltaX < 0 )
	{
		modifier = -1;
	}
	float a = (endPos.y - startPos.y)/(endPos.x - startPos.x);
	float y = startPos.y;

	glm::vec4 deltaColor = (endColor.Get() - startColor.Get())/deltaX;
	for (int i = 0; i < deltaX; i++)
	{
		Color pixelCol = Color(startColor.Get() + (deltaColor*(float)i));
		texture->SetPixel(startPos.x+(i*modifier), y, pixelCol);
		y += a;
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