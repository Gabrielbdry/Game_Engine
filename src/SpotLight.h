#pragma once
#include "PointLight.h"

class SpotLight : public PointLight {
private:

	glm::vec3 m_direction;
	float m_cutoff;
	
public:

	SpotLight(glm::vec3 direction, float cutoff, glm::vec3 position, float radius, glm::vec3 color, float intensity) : PointLight(position, radius, color, intensity) {
		m_direction = direction;
		m_cutoff = cutoff;
	}

	glm::vec3 getDirection() {
		return m_direction;
	}

	void setDirection(glm::vec3 direction) {
		m_direction = direction;
	}

	float getCutOff() {
		return m_cutoff;
	}

	void setCutOff(float cutoff) {
		m_cutoff = cutoff;
	}
};
