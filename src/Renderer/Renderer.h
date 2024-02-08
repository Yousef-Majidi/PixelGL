#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include "../Shape/Shape.h"
#include "../Shader/shaderinit.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void setNumVertices(GLuint numVertices);

	const Shader getShader() const;

	void initializeGLFW();
	void initializeGLAD();
	void initializeShader(const char*, const char*);
	void init(const Shape& shape);
	void render();

private:
	GLuint VAO{}, VBO{}, EBO{}; // OpenGL buffers
	GLuint m_numVertices{}; // Number of vertices in the VBO

	Shader m_shader{};
};
#endif // !RENDERER_H
