#ifndef OPEN_GL_APP
#define OPEN_GL_APP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGLApp
{
public:
	OpenGLApp();
	~OpenGLApp();

	void run();

private:
	const unsigned int screenWidth;
	const unsigned int screenHeight;
	GLFWwindow* window;

	bool initializeGLFW();
	bool createWindow();
	bool initializeGLAD();
	void processInput();
	void mainLoop();
	void cleanup();
	void render();
};

#endif // !OpenGLApp
