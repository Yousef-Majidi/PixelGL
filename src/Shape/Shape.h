#ifndef SHAPE_H
#define SHAPE_H

#include <glad/glad.h>

class Shape
{
public:
	Shape(float* vertices, unsigned int* indices, unsigned int numVertices);
	~Shape();

	GLuint getVAO() const;
	GLuint GetNumVertices() const;

	void generateBuffers();
	void bindBuffers();

private:
	float* m_vertices;
	unsigned int* m_indices;
	unsigned int m_numVertices;

	GLuint VAO{}, VBO{}, EBO{}; // OpenGL buffers
};
#endif // !SHAPE_H
