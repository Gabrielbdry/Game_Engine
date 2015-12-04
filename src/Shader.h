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
#include "PointLight.h"
#include "SpotLight.h"

class Shader {
private:

	static const unsigned int NUM_SHADERS = 2;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	std::map<std::string, Uniform*> m_uniforms;
	std::map<std::string, GLint> m_locations;

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

	static void CheckShaderError(const GLuint& shader, const GLuint& flag, const bool& isProgram, const std::string& errorMessage) {
		GLint success = 0;
		GLchar error[1024] = { 0 };

		if (isProgram)
			glGetProgramiv(shader, flag, &success);
		else
			glGetShaderiv(shader, flag, &success);

		if (success == GL_FALSE)
		{
			if (isProgram)
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			else
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);

			std::cerr << errorMessage << ": '" << error << "'" << std::endl;
		}
	}

	static GLuint CreateShader(std::string text, const GLenum& shaderType) {
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
		m_uniforms["baseLight"] = new Uniform("baseLight", "BaseLight");
		//m_uniforms["pointLight"] = new Uniform("pointLight", "PointLight");
		m_uniforms["spotLight"] = new Uniform("spotLight", "SpotLight");
	
		// PointLight test...
		/*m_locations["baseLight.color"] = glGetUniformLocation(m_program, "baseLight.color");
		m_locations["baseLight.intensity"] = glGetUniformLocation(m_program, "baseLight.intensity");
		m_locations["pointLight.baseLight.color"] = glGetUniformLocation(m_program, "pointLight.baseLight.color");
		m_locations["pointLight.baseLight.intensity"] = glGetUniformLocation(m_program, "pointLight.baseLight.intensity");
		m_locations["pointLight.position"] = glGetUniformLocation(m_program, "pointLight.position");
		m_locations["pointLight.radius"] = glGetUniformLocation(m_program, "pointLight.radius");*/

		// SpotLight test...
		m_locations["baseLight.color"] = glGetUniformLocation(m_program, "baseLight.color");
		m_locations["baseLight.intensity"] = glGetUniformLocation(m_program, "baseLight.intensity");
		m_locations["spotLight.pointLight.baseLight.color"] = glGetUniformLocation(m_program, "spotLight.pointLight.baseLight.color");
		m_locations["spotLight.pointLight.baseLight.intensity"] = glGetUniformLocation(m_program, "spotLight.pointLight.baseLight.intensity");
		m_locations["spotLight.pointLight.position"] = glGetUniformLocation(m_program, "spotLight.pointLight.position");
		m_locations["spotLight.pointLight.radius"] = glGetUniformLocation(m_program, "spotLight.pointLight.radius");
		m_locations["spotLight.direction"] = glGetUniformLocation(m_program, "spotLight.direction");
		m_locations["spotLight.cutoff"] = glGetUniformLocation(m_program, "spotLight.cutoff");

		/*m_uniforms["pointLight.radius"] = new Uniform("pointLight", "PointLight", glGetUniformLocation(m_program, "pointLight.radius"));
		m_uniforms["baseLight.color"] = new Uniform("baseLight", "BaseLight", glGetUniformLocation(m_program, "baseLight.color"));
		m_uniforms["baseLight.intensity"] = new Uniform("baseLight", "BaseLight", glGetUniformLocation(m_program, "baseLight.intensity"));
		m_uniforms["pointLight.baseLight.color"] = new Uniform("pointLight.baseLight", "PointLight", glGetUniformLocation(m_program, "pointLight.baseLight.color"));
		m_uniforms["pointLight.baseLight.intensity"] = new Uniform("pointLight.baseLight", "PointLight", glGetUniformLocation(m_program, "pointLight.baseLight.intensity"));
		m_uniforms["pointLight.position"] = new Uniform("pointLight", "PointLight", glGetUniformLocation(m_program, "pointLight.position"));
		m_uniforms["pointLight.radius"] = new Uniform("pointLight", "PointLight", glGetUniformLocation(m_program, "pointLight.radius"));*/

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

	void AddUniform(const std::string& name, const std::string& type) {
		GLint location = glGetUniformLocation(m_program, name.c_str());
		if (location != -1)
			m_uniforms[name] = (new Uniform(name, type, location));
		else
			std::cerr << "Error : Couldn't find uniform location!";
	}

	void updateUniforms(Transform* transform, Camera* camera, std::map<std::string, BaseLight*> lights) {
		glm::mat4 model = camera->getViewProjection() * transform->getModel();
		for (auto uniform : m_uniforms) {
			if (uniform.second->getName() == "transform") {
				setUniformMat4fv(uniform.second->getLocation(), model);
			}
			else if (uniform.second->getType() == "BaseLight") {
				setUniformBaseLight(uniform.second->getName(), lights[uniform.second->getName()]);
			}
			else if (uniform.second->getType() == "PointLight") {
				setUniformPointLight(uniform.second->getName(), dynamic_cast<PointLight*>(lights[uniform.second->getName()]));
			}
			else if (uniform.second->getType() == "SpotLight") {
				setUniformSpotLight(uniform.second->getName(), dynamic_cast<SpotLight*>(lights[uniform.second->getName()]));
			}
		}
	}

	void setUniform3fv(const GLint& location, const glm::vec3& fvec3) {
		glUniform3fv(location, 1, &fvec3[0]);
	}

	void setUniform1f(const GLint& location, const float& f) {
		glUniform1f(location, f);
	}

	void setUniformMat4fv(const GLint& location, const glm::mat4& mat) {
		glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
	}

	void setUniformBaseLight(const std::string& name, BaseLight* baseLight) {
		setUniform3fv(m_locations[name + ".color"], baseLight->getColor());
		setUniform1f(m_locations[name + ".intensity"], baseLight->getIntensity());
	}

	void setUniformPointLight(const std::string& name, PointLight* pointLight) {
		setUniformBaseLight(name + ".baseLight", pointLight);
		setUniform3fv(m_locations[name + ".position"], pointLight->getPosition());
		setUniform1f(m_locations[name + ".radius"], pointLight->getRadius());
	}

	void setUniformSpotLight(const std::string& name, SpotLight* spotLight) {
		setUniformPointLight(name + ".pointLight", spotLight);
		setUniform3fv(m_locations[name + ".direction"], spotLight->getDirection());
		setUniform1f(m_locations[name + ".cutoff"], spotLight->getCutOff());
	}
};