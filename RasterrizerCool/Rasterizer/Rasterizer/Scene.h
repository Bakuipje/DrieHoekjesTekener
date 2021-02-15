#pragma once
#include "Camera.h"
//#include "Object.h"
//#include "Mesh.h"
#include "Texture.h"
#include "Line.h"
#include <vector>

class Scene
{
public:
	Scene() {}
	void AddCamera(Camera* camera);
	//void AddObject(Object* object);
	void AddLine(Line* Line);
	void Render(Texture &texture);

	void SetActiveCamera(int cameraIndex);
	void ToggleActiveCamera();
	inline int GetNumCameras() { return m_cameras.size(); }

	inline bool IsValid() { return m_cameras.size() > 0; }

private:
	int m_CurrentCameraIndex = 0;

	std::vector<Camera*> m_cameras;
	std::vector<Line*> m_lines;
	//std::vector<Object*> m_objects;
	//std::vector<Light*> m_lights;
};

