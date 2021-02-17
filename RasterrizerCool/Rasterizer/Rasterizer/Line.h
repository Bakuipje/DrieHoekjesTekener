#pragma once
#include <glm/glm.hpp>

#include "Color.h"
#include "Texture.h"

class Line
{
public:
	Line() {}
	Line(glm::vec3 startPos, glm::vec3 endPos, Color startColor, Color endColor);
	~Line() {}

	void Render(Texture* texture);
	//Setters
	void SetStartPos(glm::vec3 pos);
	void SetEndPos(glm::vec3 pos);
	void SetStartColor(Color color);
	void SetEndColor(Color color);
	// Getter
	glm::vec3 GetStartPos();
	glm::vec3 GetEndPos();
	Color GetStartColor();
	Color GetEndColor();
private:
	glm::vec3 startPos, endPos;
	Color startColor, endColor;
};

