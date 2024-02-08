#ifndef APP
#define APP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

#include "../Shader/shaderinit.h"
#include "../Shape/Shape.h"
#include "../Renderer/Renderer.h"

class App
{
public:
	App() {};
	App(unsigned int, unsigned int, const char*, const char*);
	~App();
	void run();
	void addShape(const Shape& shape);

private:
	const char* m_vertexShaderPath = nullptr;
	const char* m_fragmentShaderPath = nullptr;
	unsigned int m_width{}, m_height{};
	GLFWwindow* m_window{};
	std::vector<Shape> m_shapes{};
	std::unique_ptr<Renderer> m_renderer;

	void createWindow(unsigned int, unsigned int);
	void init();
	void gameLoop();
	void render();
	void transform(Shader);
	void processInput(GLFWwindow*);
};

#endif // !App
