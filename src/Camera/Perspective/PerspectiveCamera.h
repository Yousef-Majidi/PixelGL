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
	PerspectiveCamera(mat4 projection, vec3 cameraPos, vec3 cameraFront, vec3 cameraUp, float fov, float aspectRatio);
	~PerspectiveCamera() {};

	void update() override;
	const bool getFreeLook() const;
	void setFreeLook(bool freeLook);
	void freeLook(float x, float y);
	void transform(vec3 newPos);
	void setSpeed(int speed);

private:
	vec3 m_cameraPos;
	vec3 m_cameraFront;
	vec3 m_cameraUp;
	float m_fov;
	float m_yaw;
	float m_pitch;
	float m_aspectRatio;
	bool m_freeLook;
	bool m_firstMouseMovement;
	int m_cameraSpeed;

	void processMouseInput(float x, float y);
};
#endif // !PERSPECTIVE_CAMERA_H
