#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Shape/Shape.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void setNumVertices(GLuint numVertices);

	void initializeGLFW();
	void initializeGLAD();
	void init();
	void render();

private:
	GLuint VAO{}, VBO{}, EBO{}; // OpenGL buffers
	GLuint m_numVertices{}; // Number of vertices in the VBO
};
#endif // !RENDERER_H
