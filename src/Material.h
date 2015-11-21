#pragma once
#include "Texture.h"

class Material {
private:

	Texture* m_texture;

public:

	Material(Texture* texture) {
		m_texture = texture;
	}

	Texture* getTexture() {
		return m_texture;
	}
};