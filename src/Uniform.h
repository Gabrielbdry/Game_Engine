#pragma once
#include <string>

class Uniform {
private:

	std::string m_name;
	std::string m_type;
	GLint m_location;

public:

	Uniform(std::string name, std::string type, GLint location) {
		m_name = name;
		m_type = type;
		m_location = location;
	}

	Uniform(std::string name, std::string type) {
		m_name = name;
		m_type = type;
	}

	std::string getName() {
		return m_name;
	}

	std::string getType() {
		return m_type;
	}

	GLint getLocation() {
		return m_location;
	}

	void setName(std::string name) {
		m_name = name;
	}

	void setType(std::string type) {
		m_type = type;
	}

	void setLocation(GLint location) {
		m_location = location;
	}
};