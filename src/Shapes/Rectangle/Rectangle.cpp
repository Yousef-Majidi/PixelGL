#include <glm/glm.hpp>
#include <glad/glad.h>
#include <iostream>
#include <vector>

#include "Rectangle.h"

Rectangle::Rectangle(glm::vec3 center, float size, glm::vec3 color)
{
	generateVertices(center, size, color);
	generateIndices();
	this->m_numVertices = getIndicesSize() / sizeof(unsigned int);
	std::cout << "number of vertices: " << m_numVertices << std::endl;

	generateBuffers();
}

Rectangle::~Rectangle()
{
	// TODO: figure this out later
	/*glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);*/
}

const std::vector<float>& Rectangle::getVertices() const
{
	return this->m_vertices;
}

const std::vector<unsigned int>& Rectangle::getIndices() const
{
	return this->m_indices;
}

const float Rectangle::getVerticesSize() const
{
	return m_vertices.size() * sizeof(float);
}

const unsigned int Rectangle::getIndicesSize() const
{
	return m_indices.size() * sizeof(unsigned int);
}

const GLuint Rectangle::getVAO() const
{
	return this->VAO;
}

const GLuint Rectangle::getEBO() const
{
	return this->EBO;
}

const GLuint Rectangle::getNumVertices() const
{
	return this->m_numVertices;
}

void Rectangle::generateVertices(glm::vec3 center, float size, glm::vec3 color)
{
	float halfSize = size / 2.0f;
	m_vertices =
	{
		center.x + halfSize, center.y + halfSize, center.z, color.r, color.g, color.b, // top right
		center.x - halfSize, center.y + halfSize, center.z, color.r, color.g, color.b, // top left
		center.x - halfSize, center.y - halfSize, center.z, color.r, color.g, color.b, // bottom left
		center.x + halfSize, center.y - halfSize, center.z, color.r, color.g, color.b // bottom right
	};
}

void Rectangle::generateIndices()
{
	m_indices = {
		0, 1, 2,  // first Triangle
		2, 3, 0   // second Triangle
	};
}

void Rectangle::generateBuffers()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, getVerticesSize(), m_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndicesSize(), m_indices.data(), GL_STATIC_DRAW);

	// position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}