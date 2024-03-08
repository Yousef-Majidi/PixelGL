#include <GLFW/glfw3.h>
#include "DeltaTime.h"

namespace PixelGL
{
	DeltaTime& DeltaTime::getInstance()
	{
		static DeltaTime instance;
		return instance;
	}

	void DeltaTime::update()
	{
		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;
	}

	float DeltaTime::getDeltaTime() const
	{
		return m_deltaTime;
	}

	float DeltaTime::getFPS() const
	{
		return 1.0f / m_deltaTime;
	}
}