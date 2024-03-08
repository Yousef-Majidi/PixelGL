#include <GLFW/glfw3.h>
#include "Camera.h"

Camera::Camera(mat4 projection)
{
	m_projection = projection;
	m_view = mat4(1.0f);
}

mat4 Camera::getProjection()
{
	return m_projection;
}

mat4 Camera::getView()
{
	return m_view;
}


