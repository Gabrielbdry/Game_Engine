#pragma once
#include <GL\glew.h>
#include <SDL2\SDL_image.h>
#include <iostream>
#include <string>
#include <cassert>

class Texture {
private:

	GLuint m_ID;

	bool Load(const char* path){

		IMG_Init(IMG_INIT_PNG);
		SDL_Surface* surface = IMG_Load(path);

		if (surface != nullptr){
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &m_ID);
			glBindTexture(GL_TEXTURE_2D, m_ID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

			SDL_FreeSurface(surface);
			return true;
		}

		return false;
	}

public:

	Texture(const std::string& fileName) {
		if (!Load(fileName.c_str())) {
			std::cerr << "Texture loading failed for texture: " << fileName << std::endl;
		}
	}

	~Texture() {
		glDeleteTextures(1, &m_ID);
	}

	void Bind() {
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
};