#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <GL\glew.h>
#include "Transform.h"
#include "Camera.h"
#include "Uniform.h"
#include "BaseLight.h"

class Shader {
private:

	static const unsigned int NUM_SHADERS = 2;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	std::map<std::string, Uniform*> m_uniforms;

	static std::string LoadShader(const std::string& fileName) {
		std::ifstream file;
		file.open(fileName.c_str());

		std::string output;
		std::string line;

		if (file.is_open()) {
			while (file.good()) {
				getline(file, line);
				output.append(line + "\n");
			}
		}
		else {
			std::cerr << "Unable to load shader: " << fileName << std::endl;
		}

		return output;
	}

	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
		GLuint success = 0;
		GLchar error[1024] = { 0 };
	}

	static GLuint CreateShader(const std::string& text, GLenum shaderType) {
		GLuint shader = glCreateShader(shaderType);

		if (shader == 0)
			std::cerr << "Error: shader creation failed!" << std::endl;

		const GLchar* shaderSourcesString[1];
		GLint shaderSourceStringsLengths[1];

		shaderSourcesString[0] = text.c_str();
		shaderSourceStringsLengths[0] = text.length();

		glShaderSource(shader, 1, shaderSourcesString, shaderSourceStringsLengths);
		glCompileShader(shader);

		CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

		return shader;
	}

public:

	Shader(const std::string& fileName) {
		m_program = glCreateProgram();

		m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
		m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

		for (unsigned int i = 0; i < NUM_SHADERS; i++) {
			glAttachShader(m_program, m_shaders[i]);
		}

		glBindAttribLocation(m_program, 0, "position");
		glBindAttribLocation(m_program, 1, "texCoord");
		glBindAttribLocation(m_program, 2, "normal");

		glLinkProgram(m_program);
		CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: program linking failed: ");

		glValidateProgram(m_program);
		CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: program is invalid: ");

		m_uniforms["transform"] = new Uniform("transform", "Matrix4fv", glGetUniformLocation(m_program, "transform"));
		m_uniforms["baseLight.color"] = new Uniform("baseLight", "BaseLight", glGetUniformLocation(m_program, "baseLight.color"));
		m_uniforms["baseLight.intensity"] = new Uniform("baseLight", "BaseLight", glGetUniformLocation(m_program, "baseLight.intensity"));
	}

	~Shader() {

		for (unsigned int i = 0; i < NUM_SHADERS; i++) {
			glDetachShader(m_program, m_shaders[i]);
			glDeleteShader(m_shaders[i]);
		}

		glDeleteProgram(m_program);
	}

	void bind() {
		glUseProgram(m_program);
	}

	void AddUniform(std::string name, std::string type) {
		GLint location = glGetUniformLocation(m_program, name.c_str());
		m_uniforms[name] = (new Uniform(name, type, location));
	}

	void updateUniforms(Transform* transform, Camera* camera, std::map<std::string, BaseLight*> lights) {
		glm::mat4 model = camera->getViewProjection() * transform->getModel();
		for (auto uniform : m_uniforms) {
			if (uniform.second->getName() == "transform") {
				glUniformMatrix4fv(uniform.second->getLocation(), 1, GL_FALSE, &model[0][0]);
			}
			else if (uniform.second->getType() == "BaseLight") {
				setUniformBaseLight(uniform.second->getName(), lights[uniform.second->getName()]);
			}
		}
	}

	void setUniform3fv(GLint location, glm::vec3 fvec3) {
		glUniform3fv(location, 1, &fvec3[0]);
	}

	void setUniform1f(GLint location, float f) {
		glUniform1f(location, f);
	}

	void setUniformBaseLight(std::string name, BaseLight* baseLight) {
		glUniform3fv(m_uniforms[name + ".color"]->getLocation(), 1, &baseLight->getColor()[0]);
		glUniform1f(m_uniforms[name + ".intensity"]->getLocation(), baseLight->getIntensity());
	}
};