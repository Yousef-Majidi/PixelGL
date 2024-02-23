#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Color/Color.h"
#include "../Shape.h"
#include "Rectangle.h"

using glm::mat4;
using glm::vec3;

Rectangle::Rectangle(vec3 center, float size, Color color) : Shape(center, size, color)
{
	//m_transform = mat4{ 1.0f };
	//m_rotation = mat4{ 1.0f };
	//m_translation = mat4{ 1.0f };
	//m_scale = mat4{ 1.0f };
	generateVertices(center, size, color.getRGB());
	generateIndices();
	this->m_numVertices = getIndicesSize() / sizeof(unsigned int);
	generateBuffers();
}

Rectangle::~Rectangle()
{
	// TODO: figure this out later
	/*glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);*/
}

//const GLuint Rectangle::getVAO() const
//{
//	return this->VAO;
//}

//const GLuint Rectangle::getEBO() const
//{
//	return this->EBO;
//}

//const GLuint Rectangle::getNumVertices() const
//{
//	return this->m_numVertices;
//}

//const mat4 Rectangle::getTransform() const
//{
//	return this->m_transform;
//}

void Rectangle::render() const
{
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glDrawElements(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, 0);
}

//void Rectangle::resetRotation()
//{
//	m_rotation = mat4(1.0f);
//	updateTransform();
//}

//void Rectangle::resetPosition()
//{
//	m_translation = mat4(1.0f);
//	updateTransform();
//}

//void Rectangle::resetScale()
//{
//	m_scale = mat4(1.0f);
//	updateTransform();
//}

//void Rectangle::rotate(float angle)
//{
//	mat4 translate = glm::translate(mat4(1.0f), -m_center);
//	mat4 rotate = glm::rotate(mat4(1.0f), glm::radians(angle), vec3(0.0f, 0.0f, 1.0f));
//	mat4 translateBack = glm::translate(mat4(1.0f), m_center);
//	m_rotation = translateBack * rotate * translate * m_rotation;
//	updateTransform();
//}

//void Rectangle::scale(float scaleFactor)
//{
//	mat4 translate = glm::translate(mat4(1.0f), -m_center);
//	mat4 scale = glm::scale(mat4(1.0f), vec3(scaleFactor, scaleFactor, scaleFactor));
//	mat4 translateBack = glm::translate(mat4(1.0f), m_center);
//	m_scale = translateBack * scale * translate;
//	updateTransform();
//}

//void Rectangle::moveTo(vec3 newPosition)
//{
//	vec3 translationVector = newPosition - m_center;
//	m_translation = glm::translate(mat4(1.0f), translationVector);
//	updateTransform();
//}

//const float Rectangle::getVerticesSize() const
//{
//	return m_vertices.size() * sizeof(float);
//}

const unsigned int Rectangle::getIndicesSize() const
{
	return m_indices.size() * sizeof(unsigned int);
}

void Rectangle::generateVertices(vec3 center, float size, vec3 color)
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
		0, 1, 2,
		2, 3, 0
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

//void Rectangle::updateTransform()
//{
//	m_transform = m_translation * m_rotation * m_scale;
//}
