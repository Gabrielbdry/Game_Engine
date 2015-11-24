#pragma once
#include <map>
#include <string>
#include "Singleton.h"
#include "GameObject.h"

class Shader;
class BaseLight;
class Camera;

class RenderEngine : public Singleton<RenderEngine> {
private:

	Camera* m_mainCam;
	Shader* m_shader;
	std::map<std::string, BaseLight*> m_lights;

public:

	void RenderObject(GameObject* object) {
		object->Render(m_shader, m_mainCam, m_lights);
	}

	BaseLight* getLight(std::string name) {
		return m_lights[name];
	}

	void addLight(BaseLight* light, std::string name) {
		m_lights[name] = light;
	}

	void setCamera(Camera* camera) {
		m_mainCam = camera;
	}

	void setShader(Shader* shader) {
		m_shader = shader;
	}

};