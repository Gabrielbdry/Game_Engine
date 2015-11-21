#include <iostream>
#include <SDL2\SDL.h>
#include "glm\gtx\normalize_dot.hpp"
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Camera.h"
#include "obj_loader.h"
#include "Model.h"
#include "RessourceManager.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv) {

	SDL_Init(SDL_INIT_EVERYTHING);
	Display display(800, 600, "Hello world!");

	Shader shader("./res/basicShader");

	RessourceManager::getInstance().addMesh("./res/wall.obj");
	RessourceManager::getInstance().addTexture("./res/wall.png");

	Camera camera(glm::vec3(0, 0, -10), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	Model wall(RessourceManager::getInstance().getTexture("./res/wall.png"), RessourceManager::getInstance().getMesh("./res/wall.obj"));
	wall.getTransform().setRot(glm::vec3(80, 0, 0));

	while (!display.isClosed()) {
		display.clear(0.0f, 0.15f, 0.3f, 1.0f);

		shader.bind();
		wall.show(shader, camera);

		display.swapBuffer();
	}
	return 0;
}