#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"

class Model {
private:

	Texture* m_texture;
	Mesh* m_mesh;

	Transform m_transform;

public:

	Model(Texture* texture, Mesh* mesh) {
		m_texture = texture;
		m_mesh = mesh;
	}

	void show(Shader& shader, Camera& cam) {
		m_texture->Bind();
		shader.update(m_transform, cam);
		m_mesh->Draw();
	}

	Transform& getTransform() {
		return m_transform;
	}
};