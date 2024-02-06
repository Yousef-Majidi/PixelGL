#include <glad/glad.h>

#include "Shape.h"

Shape::Shape(float* vertices, unsigned int* indices, unsigned int numVertices) : m_vertices(vertices), m_indices(indices), m_numVertices(numVertices) {}

Shape::~Shape()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

GLuint Shape::getVAO() const
{
	return this->VAO;
}

GLuint Shape::GetNumVertices() const
{
	return this->m_numVertices;
}

void Shape::generateBuffers()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
}

void Shape::bindBuffers()
{
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

    // position attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute pointer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
