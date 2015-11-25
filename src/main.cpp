#include <iostream>
#include <SDL2\SDL.h>
#include "glm\gtx\normalize_dot.hpp"
#include "Display.h"
#include "RenderEngine.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Camera.h"
#include "obj_loader.h"
#include "RessourceManager.h"
#include "BaseLight.h"
#include "PointLight.h"
#include "GameComponent.h"
#include "GameObject.h"
#include "MeshRenderer.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv) {

	SDL_Init(SDL_INIT_EVERYTHING);
	Display display(800, 600, "Hello world!");

	RenderEngine::getInstance().setCamera(new Camera(glm::vec3(3, 0, -0.5), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f));
	RenderEngine::getInstance().setShader(new Shader("./res/basicShader"));

	RessourceManager::getInstance().addMesh("./res/room.obj");
	RessourceManager::getInstance().addTexture("./res/room.png");

	GameObject* room = new GameObject();

	room->addComponent(new MeshRenderer(RessourceManager::getInstance().getMesh("./res/room.obj"), new Material(RessourceManager::getInstance().getTexture("./res/room.png"))));

	RenderEngine::getInstance().addLight(new BaseLight(glm::vec3(0.1, 0.1, 0.1), 1.0f), "baseLight", LIGHT_BASE);
	RenderEngine::getInstance().addLight(new PointLight(glm::vec3(0.0, 0.0, 0.0), 1.0f, glm::vec3(1.0, 1.0, 1.0), 1.0f), "pointLight.baseLight", LIGHT_POINT);
	
	while (!display.isClosed()) {
		display.clear(0.0f, 0.15f, 0.3f, 1.0f);

		RenderEngine::getInstance().RenderObject(room);

		display.swapBuffer();
	}
	return 0;
}