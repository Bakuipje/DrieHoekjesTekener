#include "Scene.h"

void Scene::AddCamera(Camera* camera)
{
	m_cameras.push_back(camera);
}

void Scene::AddLine(Line* line)
{
	m_lines.push_back(line);
}
void Scene::Render(Texture &texture)
{
	if (!this->IsValid())
	{
		return;
	}

	m_cameras[m_CurrentCameraIndex]->Render(m_lines, texture);
}

void Scene::SetActiveCamera(int cameraIndex)
{
	assert(cameraIndex >= 0 && cameraIndex < this->GetNumCameras());

	m_CurrentCameraIndex = cameraIndex;
}

void Scene::ToggleActiveCamera()
{
	int newCameraIndex = m_CurrentCameraIndex + 1;
	if (newCameraIndex >= this->GetNumCameras())
	{
		newCameraIndex = 0;
	}

 	this->SetActiveCamera(newCameraIndex);
}
