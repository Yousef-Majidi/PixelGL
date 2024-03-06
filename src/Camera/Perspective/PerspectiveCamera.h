#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../Camera.h"

using glm::mat4;
using glm::vec3;

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera() = delete;
	PerspectiveCamera(mat4 projection, GLFWwindow* window, vec3 cameraPos, vec3 cameraFront, vec3 cameraUp, float fov);
	~PerspectiveCamera() {};

	void update() override;
	const bool getFreeLook() const;
	void setFreeLook(bool freeLook);
	void freeLook(float x, float y);

private:
	vec3 m_cameraPos;
	vec3 m_cameraFront;
	vec3 m_cameraUp;
	float m_fov;
	float m_yaw;
	float m_pitch;
	bool m_freeLook;
	bool m_firstMouseMovement;

	float getAspectRatio();
	void processKeyboardInput() override;
	void processMouseInput(float x, float y);
};
#endif // !PERSPECTIVE_CAMERA_H
