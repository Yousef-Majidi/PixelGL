#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include "../../Color/Color.h"
#include "../Shape.h"
#include "Rectangle.h"

using glm::mat4;
using glm::vec3;

Rectangle::Rectangle(vec3 center, float size, Color color) : Shape(center, color)
{
	generateVertices(center, size, color.getRGB());
	generateIndices();
	generateBuffers(6);
}

Rectangle::Rectangle(vec3 center, float height, float width, Color color) : Shape(center, color)
{
	generateVertices(center, height, width, color.getRGB());
	generateIndices();
	generateBuffers(6);
}

void Rectangle::render() const
{
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glDrawElements(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, 0);
}

void Rectangle::generateVertices(vec3 center, float size, vec3 color)
{
	float halfSize = size / 2.0f;
	m_vertices =
	{
		center.x + halfSize, center.y + halfSize, center.z, color.r, color.g, color.b, // top right
		center.x + halfSize, center.y - halfSize, center.z, color.r, color.g, color.b, // bottom right
		center.x - halfSize, center.y - halfSize, center.z, color.r, color.g, color.b, // bottom left
		center.x - halfSize, center.y + halfSize, center.z, color.r, color.g, color.b, // top left
	};
}

void Rectangle::generateVertices(vec3 center, float height, float width, vec3 color)
{
	float halfHeight = height / 2.0f;
	float halfWidth = width / 2.0f;
	m_vertices =
	{
		center.x + halfWidth, center.y + halfHeight, center.z, color.r, color.g, color.b, // top right
		center.x + halfWidth, center.y - halfHeight, center.z, color.r, color.g, color.b, // bottom right
		center.x - halfWidth, center.y - halfHeight, center.z, color.r, color.g, color.b, // bottom left
		center.x - halfWidth, center.y + halfHeight, center.z, color.r, color.g, color.b, // top left
	};
}

void Rectangle::generateBuffers(int bufferSize)
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, bufferSize * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, bufferSize * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Rectangle::generateIndices()
{
	m_indices = {
		0, 1, 2,
		2, 3, 0
	};
	this->m_numVertices = getIndicesSize() / sizeof(unsigned int);
}

const unsigned int Rectangle::getIndicesSize() const
{
	return m_indices.size() * sizeof(unsigned int);
}