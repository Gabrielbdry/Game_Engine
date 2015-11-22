#pragma once
#include "GameComponent.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"

class MeshRenderer : public GameComponent {
private:

	Mesh* m_mesh;
	Material* m_material;

public:

	MeshRenderer(Mesh* mesh, Material* material) {
		m_mesh = mesh;
		m_material = material;
	}

	void Render(Shader* shader, Transform* transform, Camera* camera) {
		shader->bind();
		m_material->getTexture()->Bind();
		shader->updateUniforms(transform, camera);
		m_mesh->Draw();
	}
};