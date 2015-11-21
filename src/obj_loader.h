// This simple object loader loads files ordered like the following
/*
v x y z
v x y z
v x y z
vt x y
vt x y
vt x y
vn x y z
vn x y z
vn x y z
f v/vt/vn v/vt/vn v/vt/vn
*/

#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <glm\glm.hpp>

class OBJModel {
private:

	glm::vec2 parseObjVec2(const std::string& line) {

		std::string buf;
		std::stringstream ss(line);

		std::vector<std::string> tokens;

		while (ss >> buf)
			tokens.push_back(buf);

		return glm::vec2(SDL_atof(tokens[1].c_str()), SDL_atof(tokens[2].c_str()));
	}

	glm::vec3 parseObjVec3(const std::string& line) {
		
		std::string buf;
		std::stringstream ss(line);

		std::vector<std::string> tokens;

		while (ss >> buf)
			tokens.push_back(buf);
		
		return glm::vec3(SDL_atof(tokens[1].c_str()), SDL_atof(tokens[2].c_str()), SDL_atof(tokens[3].c_str()));
	}

	std::vector<glm::ivec3> parseObjFace(const std::string& line) {
		
		std::vector<glm::ivec3> out = { glm::vec3(), glm::vec3(), glm::vec3() };

		std::string buf;
		std::stringstream ss(line);

		std::vector<std::string> tokens;

		while (ss >> buf)
			tokens.push_back(buf);

		unsigned int pos1, pos2;
		pos1 = tokens[1].find_first_of('/');
		pos2 = tokens[1].find_last_of('/');
		out[0].x = SDL_atoi(tokens[1].substr(0, pos1).c_str()) - 1;
		out[1].x = SDL_atoi(tokens[1].substr(pos1 + 1, pos2 - pos1).c_str()) - 1;
		out[2].x = SDL_atoi(tokens[1].substr(pos2 + 1).c_str()) - 1;

		pos1 = tokens[2].find_first_of("/");
		pos2 = tokens[2].find_last_of("/");
		out[0].y = SDL_atoi(tokens[2].substr(0, pos1).c_str()) - 1;
		out[1].y = SDL_atoi(tokens[2].substr(pos1 + 1, pos2 - pos1).c_str()) - 1;
		out[2].y = SDL_atoi(tokens[2].substr(pos2 + 1).c_str()) - 1;

		pos1 = tokens[3].find_first_of("/");
		pos2 = tokens[3].find_last_of("/");
		out[0].z = SDL_atoi(tokens[3].substr(0, pos1).c_str()) - 1;
		out[1].z = SDL_atoi(tokens[3].substr(pos1 + 1, pos2 - pos1).c_str()) - 1;
		out[2].z = SDL_atoi(tokens[3].substr(pos2 + 1).c_str()) - 1;

		return out;
	}

public:

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_texCoord;
	std::vector<glm::vec3> m_normals;
	unsigned int nbrVertices;

	OBJModel(const std::string& fileName) {
		load(fileName.c_str());
	}

	bool load(const char* chemin){
		std::ifstream file(chemin);
		if (file.is_open()) {
			
			std::string line;

			/* Vecteurs temporaires contenant les vertices, texCoord et normals,
				ils seront utilisé pour ordonner ceux-ci selon les indices*/
			std::vector<glm::vec3> vertices_tmp;
			std::vector<glm::vec2> texCoord_tmp;
			std::vector<glm::vec3> normals_tmp;

			std::vector<glm::ivec3> indices;

			// Boucle jusqu'à la fin du fichier...
			while (!file.eof()) {

				getline(file, line);

				switch (line[0]) {
				case 'v':
					switch (line[1]) {
					case ' ': // Vertives
						vertices_tmp.push_back(parseObjVec3(line));
						break;
					case 't': // TexCoord
						texCoord_tmp.push_back(parseObjVec2(line));
						break;
					case 'n': // Normals
						normals_tmp.push_back(parseObjVec3(line));
						break;
					}
					break;
				case 'f': // Indices
					indices = parseObjFace(line);

					m_vertices.push_back(vertices_tmp[indices[0].x]);
					m_vertices.push_back(vertices_tmp[indices[0].y]);
					m_vertices.push_back(vertices_tmp[indices[0].z]);

					m_texCoord.push_back(texCoord_tmp[indices[1].x]);
					m_texCoord.push_back(texCoord_tmp[indices[1].y]);
					m_texCoord.push_back(texCoord_tmp[indices[1].z]);

					m_normals.push_back(normals_tmp[indices[2].x]);
					m_normals.push_back(normals_tmp[indices[2].y]);
					m_normals.push_back(normals_tmp[indices[2].z]);

					break;
				default:
					std::cerr << "Error : Invalid obj file!";
					return false;
					break;
				}
			}
		}
		else {
			std::cerr << "Error : Couldn't open file!";
			return false;
		}

		file.close();
		return true;
	}

	unsigned int obtNbrSommets(){
		return  nbrVertices / 3;
	}

};