#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Shader/shaderinit.h"
#include "Renderer.h"

namespace PixelGL
{
	namespace Renderer
	{
		using PixelGL::Shader::Shader;

		Renderer::Renderer() {}
		Renderer::~Renderer() {}

		Shader Renderer::getShader() const
		{
			return m_shader;
		}

		void Renderer::initializeGLFW()
		{
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		}

		void Renderer::initializeGLAD()
		{
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return;
			}
		}

		void Renderer::initializeShader(const char* vertexShaderPath, const char* fragmentShaderPath)
		{
			m_shader = Shader(vertexShaderPath, fragmentShaderPath);
		}
	}
}