#pragma once
#include <map>
#include "GameComponent.h"
#include "Mesh.h"
#include "Material.h"

class BaseLight;
class Camera;
class Shader;
class Transform;

class MeshRenderer : public GameComponent {
private:

	Mesh* m_mesh;
	Material* m_material;

public:

	MeshRenderer(Mesh* mesh, Material* material) {
		m_mesh = mesh;
		m_material = material;
	}

	void Render(Shader* shader, Transform* transform, Camera* camera, std::map<std::string, BaseLight*> lights) {
		shader->bind();
		m_material->getTexture()->Bind();
		shader->updateUniforms(transform, camera, lights);
		m_mesh->Draw();
	}
};