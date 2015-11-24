#pragma once
#include <map>
#include <string>

class Camera;
class Transform;
class Shader;
class BaseLight;

class GameComponent {
private:

public:

	virtual void Render(Shader* shader, Transform* transform, Camera* camera, std::map<std::string, BaseLight*> lights) {}
};