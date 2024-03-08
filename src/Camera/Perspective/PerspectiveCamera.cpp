#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../Camera.h"
#include "PerspectiveCamera.h"

// DEBUG 
static float DELTA_TIME = 0.0f;
static float LAST_FRAME = 0.0f;
// DEBUG
PerspectiveCamera::PerspectiveCamera(mat4 projection, vec3 cameraPos, vec3 cameraFront, vec3 cameraUp, float fov, float aspectRatio) : Camera(projection)
{
	m_cameraPos = cameraPos;
	m_cameraFront = cameraFront;
	m_cameraUp = cameraUp;
	m_fov = fov;
	m_freeLook = false;
	m_firstMouseMovement = true;
	m_yaw = -90.0f;
	m_pitch = 0.0f;
	m_aspectRatio = aspectRatio;
	m_cameraSpeed = 1;
}

void PerspectiveCamera::update()
{
	float currentFrame = glfwGetTime();
	DELTA_TIME = currentFrame - LAST_FRAME;
	LAST_FRAME = currentFrame;
	m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
	m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, 0.1f, 100.0f);
}

const bool PerspectiveCamera::getFreeLook() const
{
	return m_freeLook;
}

void PerspectiveCamera::setFreeLook(bool freeLook)
{
	m_freeLook = freeLook;
	if (!m_freeLook)
		m_firstMouseMovement = true;
}

void PerspectiveCamera::freeLook(float x, float y)
{
	if (m_freeLook)
		processMouseInput(x, y);
}

void PerspectiveCamera::zoom(float yoffset)
{
	m_cameraPos += yoffset * m_cameraFront;
	if (m_cameraPos.z < 5.0f)
		m_cameraPos.z = 5.0f;
	if (m_cameraPos.z > 25.0f)
		m_cameraPos.z = 25.0f;
}

void PerspectiveCamera::transform(vec3 newPos)
{
	m_cameraPos += m_cameraSpeed * DELTA_TIME * newPos;
}

void PerspectiveCamera::setSpeed(int speed)
{
	m_cameraSpeed = speed;
}

void PerspectiveCamera::processMouseInput(float x, float y)
{
	static float lastX = 0.0f;
	static float lastY = 0.0f;
	if (m_firstMouseMovement)
	{
		lastX = x;
		lastY = y;
		m_firstMouseMovement = false;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y; // reversed since y-coordinates go from bottom to top
	lastX = x;
	lastY = y;

	float sensitivity = 0.1f; // a ratio that define how sensitive the mouse movement will be
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;
	glm::vec3 front{};
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_cameraFront = glm::normalize(front);
}

