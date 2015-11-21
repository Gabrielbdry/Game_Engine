#pragma once
#include "Camera.h"
#include "Singleton.h"
#include "GameObject.h"

class RenderEngine : public Singleton<RenderEngine> {
private:

	Camera* m_mainCam;
	Shader* m_shader;

public:

	void RenderObject(GameObject* object) {
		object->Render(m_shader, m_mainCam);
	}

	void setCamera(Camera* camera) {
		m_mainCam = camera;
	}

	void setShader(Shader* shader) {
		m_shader = shader;
	}

};