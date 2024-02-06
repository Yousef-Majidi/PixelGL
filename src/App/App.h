#ifndef APP
#define APP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Shader/shaderinit.h"
#include "../Shape/Shape.h"

class App
{
public:
	App() {};
	App(unsigned int, unsigned int, const char*, const char*);
	~App();
	void run();
	void addShape(Shape shape);

private:
	const char* m_vertexShaderPath = nullptr;
	const char* m_fragmentShaderPath = nullptr;
	unsigned int m_width{}, m_height{};
	Shader m_shader{};
	GLFWwindow* m_window{};
	GLuint m_numVertices{}; // Number of vertices in the VBO
	GLuint VAO{}, VBO{}, EBO{}; // OpenGL buffers

	void initializeGLFW();
	void createWindow(unsigned int, unsigned int);
	void initializeGLAD();
	void initializeShader(const char*, const char*);
	void init();
	void gameLoop();
	void render();
	void transform(Shader);
	void processInput(GLFWwindow*);
};

#endif // !App
