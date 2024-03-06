#include <GLFW/glfw3.h>
#include "Camera.h"

Camera::Camera(mat4 projection, GLFWwindow* window)
{
	m_projection = projection;
	m_view = mat4(1.0f);
	m_window = window;
}

mat4 Camera::getProjection()
{
	return this->m_projection;
}

mat4 Camera::getView()
{
	return this->m_view;
}


