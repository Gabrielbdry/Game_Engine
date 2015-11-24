#pragma once
#include <list>
#include <map>
#include <string>
#include "BaseLight.h"
#include "GameComponent.h"
#include "Transform.h"

class Camera;
class Shader;

class GameObject {
private:

	std::list<GameComponent*> m_components;
	Transform* m_transform;

public:

	GameObject() {
		m_transform = new Transform();
	}

	void addComponent(GameComponent* component) {
		m_components.push_back(component);
	}

	void Render(Shader* shader, Camera* camera, std::map<std::string, BaseLight*> lights) {
		for (GameComponent* it : m_components) {
			it->Render(shader, m_transform, camera, lights);
		}

	}

	Transform* getTransform() {
		return m_transform;
	}
};