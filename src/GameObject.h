#pragma once
#include <list>
#include "GameComponent.h"
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"

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

	void Render(Shader* shader, Camera* camera) {
		for (GameComponent* it : m_components) {
			it->Render(shader, m_transform, camera);
		}

	}

	Transform* getTransform() {
		return m_transform;
	}
};