#pragma once
#include "BaseLight.h"

class PointLight : public BaseLight {
private:

	glm::vec3 m_position;
	float m_radius;

public:

	PointLight(glm::vec3 position, float radius, glm::vec3 color, float intensity) : BaseLight(color, intensity) {
		m_position = position;
		m_radius = radius;
	}

	glm::vec3 getPosition() {
		return m_position;
	}

	void setPosition(glm::vec3 position) {
		m_position = position;
	}

	float getRadius() {
		return m_radius;
	}

	void setRadius(float radius) {
		m_radius = radius;
	}
};