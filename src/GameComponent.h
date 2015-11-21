#pragma once
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

class GameComponent {
private:

public:

	virtual void Render(Shader* shader, Transform* transform, Camera* camera) {}
};