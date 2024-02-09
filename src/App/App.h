#ifndef APP_H
#define APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include "../Renderer/Renderer.h"
#include "../Shapes/Rectangle/Rectangle.h"

class App
{
public:
	App() {};
	App(unsigned int, unsigned int, const char*, const char*);
	~App();
	void run();
	void addShape(const Rectangle& shape);

private:
	const char* m_vertexShaderPath = nullptr;
	const char* m_fragmentShaderPath = nullptr;
	GLFWwindow* m_window{};
	std::vector<Rectangle> m_shapes{};
	std::unique_ptr<Renderer> m_renderer;

	void createWindow(unsigned int, unsigned int);
	void init();
	void gameLoop();
	void render();

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif // !App_H