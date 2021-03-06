#pragma once
#include <glm\glm.hpp>
#include <GL/glew.h>
#include "obj_loader.h"
#include <vector>

class Mesh {
private:

	enum {
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

	void initMesh(const OBJModel& model) {

		m_drawCount = model.m_vertices.size();

		glGenVertexArrays(1, &m_vertexArrayObject);
		glBindVertexArray(m_vertexArrayObject);

		glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

		//Position
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, model.m_vertices.size() * sizeof(model.m_vertices[0]), &model.m_vertices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
		
		//TexCoords
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
		glBufferData(GL_ARRAY_BUFFER, model.m_vertices.size() * sizeof(model.m_texCoord[0]), &model.m_texCoord[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

		//Normals
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
		glBufferData(GL_ARRAY_BUFFER, model.m_normals.size() * sizeof(model.m_normals[0]), &model.m_normals[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);

		glBindVertexArray(0);
	}

public:

	Mesh(const std::string& fileName) {
		OBJModel model = OBJModel(fileName);
		initMesh(model);
	}

	~Mesh() {
		glDeleteVertexArrays(1, &m_vertexArrayObject);
		glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	}

	void Draw() {
		glBindVertexArray(m_vertexArrayObject);

		glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

		glBindVertexArray(0);
	}
};