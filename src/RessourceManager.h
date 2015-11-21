#pragma once
#include "Singleton.h"
#include "Texture.h"
#include "Mesh.h"
#include <map>

class RessourceManager : public Singleton<RessourceManager> {
private:

	std::map<std::string, Texture*> m_textures;
	std::map<std::string, Mesh*> m_meshes;

public:

	bool addTexture(std::string path) {
		if (m_textures.find(path) == m_textures.end())
			return m_textures[path] = new Texture(path);
		return false;
	}

	bool addMesh(std::string path) {
		if (m_meshes.find(path) == m_meshes.end())
			return m_meshes[path] = new Mesh(path);
		return false;
	}

	bool removeTexture(std::string path) {
		if (m_textures.find(path) != m_textures.end()) {
			m_textures.erase(path);
			return true;
		}

		return false;
	}

	bool removeMesh(std::string path) {
		if (m_meshes.find(path) != m_meshes.end()) {
			m_meshes.erase(path);
			return true;
		}

		return false;
	}

	Texture* getTexture(std::string path) {
		if (m_textures.find(path) != m_textures.end())
			return m_textures[path];

		return nullptr;
	}

	Mesh* getMesh(std::string path) {
		if (m_meshes.find(path) != m_meshes.end())
			return m_meshes[path];

		return nullptr;
	}

	void make_empty() {
		for (auto it : m_textures) {
			delete it.second;
		}
		m_textures.clear();
		for (auto it : m_meshes) {
			delete it.second;
		}
		m_meshes.clear();
	}
};