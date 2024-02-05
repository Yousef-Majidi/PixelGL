#ifndef OPEN_GL_APP
#define OPEN_GL_APP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "shader/shaderinit.h"

class OpenGLApp
{
public:
	OpenGLApp() {};
	OpenGLApp(unsigned int width, unsigned int height);
	~OpenGLApp();
	void run();

private:
	unsigned int m_width{}, m_height{};
	Shader m_shader{};
	GLFWwindow* m_window{};
	GLuint m_numVertices{}; // Number of vertices in the VBO
	GLuint VAO{}, VBO{}, EBO{}; // OpenGL buffers

	void initializeGLFW();
	void createWindow(unsigned int, unsigned int);
	void initializeGLAD();
	void initializeShader();
	void init();
	void gameLoop();
	void render();
	void transform(Shader);
	void processInput(GLFWwindow*);
};

#endif // !OpenGLApp
