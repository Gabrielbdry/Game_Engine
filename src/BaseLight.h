#pragma once
#include "GameComponent.h"

class BaseLight : public GameComponent {
private:

	glm::vec3 m_color;
	float m_intensity;

public:

	BaseLight(glm::vec3 color, float intensity) {
		m_color = color;
		m_intensity = intensity;
	}

	glm::vec3 getColor() {
		return m_color;
	}

	float getIntensity() {
		return m_intensity;
	}

	void setColor(glm::vec3 color) {
		m_color = color;
	}

	void setIntensity(float intensity) {
		m_intensity = intensity;
	}
};