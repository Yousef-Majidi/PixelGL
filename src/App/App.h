#ifndef APP_H
#define APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include "../Camera/Camera.h"
#include "../Renderer/Renderer.h"
#include "../Shapes/Shape.h"

namespace PixelGL
{
	namespace App
	{
		class App
		{
		public:
			App() {};
			App(unsigned int, unsigned int, const char*, const char*);
			~App();
			void run();
			void addShape(PixelGL::Shape::Shape* shape);

		private:
			const char* m_vertexShaderPath = nullptr;
			const char* m_fragmentShaderPath = nullptr;
			GLFWwindow* m_window{};
			std::vector<PixelGL::Shape::Shape*> m_shapes{};
			std::unique_ptr<PixelGL::Renderer::Renderer> m_renderer;
			std::unique_ptr<PixelGL::Camera::Camera> m_camera;

			void createWindow(unsigned int, unsigned int);
			void initializeShapes();
			void initializeCamera();
			void gameLoop();
			void render();
			void processKeyboardInput();

			static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
			static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
			static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		};
	}
}
#endif // !App_H