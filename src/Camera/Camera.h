#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>


using glm::mat4;

class Camera
{
public:
	Camera() = delete;
	Camera(mat4 projection, GLFWwindow* window);
	~Camera() {};

	virtual void update() = 0;
	virtual void processMouseInput(float x, float y) = 0;

	mat4 getProjection();
	mat4 getView();

protected:
	mat4 m_projection;
	mat4 m_view;
	GLFWwindow* m_window;

	virtual void processKeyboardInput() = 0;
};
#endif // !CAMERA_H
