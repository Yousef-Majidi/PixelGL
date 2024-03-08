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

		private:
			GLFWwindow* m_window{};
			std::vector<std::unique_ptr<PixelGL::Shape::Shape>> m_uniqueShapes{};
			std::unique_ptr<PixelGL::Renderer::Renderer> m_renderer;
			std::unique_ptr<PixelGL::Camera::Camera> m_camera;

			void createWindow(unsigned int, unsigned int);
			void setCallbacks();
			void initializeShapes();
			void initializeCamera();
			void addShape(PixelGL::Shape::Shape* shape);
			void gameLoop();
			void render();
			void processKeyboardInput();

			static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
			static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
			static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
		};
	}
}
#endif // !App_H