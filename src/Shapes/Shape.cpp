#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Color/Color.h"
#include "Shape.h"

using glm::vec3;
using glm::mat4;

Shape::Shape(vec3 center, Color color) : m_center(center), m_color(color)
{
	m_transform = mat4{ 1.0f };
	m_rotation = mat4{ 1.0f };
	m_translation = mat4{ 1.0f };
	m_scale = mat4{ 1.0f };
}

Shape::~Shape()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

void Shape::resetRotation()
{
	m_rotation = mat4(1.0f);
	updateTransform();
}

void Shape::resetPosition()
{
	m_translation = mat4(1.0f);
	updateTransform();
}

void Shape::resetScale()
{
	m_scale = mat4(1.0f);
	updateTransform();
}

void Shape::rotate(float angle)
{
	mat4 translate = glm::translate(mat4(1.0f), -m_center);
	mat4 rotate = glm::rotate(mat4(1.0f), glm::radians(angle), vec3(0.0f, 0.0f, 1.0f));
	mat4 translateBack = glm::translate(mat4(1.0f), m_center);
	m_rotation = translateBack * rotate * translate * m_rotation;
	updateTransform();
}

void Shape::scale(float scaleFactor)
{
	mat4 translate = glm::translate(mat4(1.0f), -m_center);
	mat4 scale = glm::scale(mat4(1.0f), vec3(scaleFactor, scaleFactor, scaleFactor));
	mat4 translateBack = glm::translate(mat4(1.0f), m_center);
	m_scale = translateBack * scale * translate;
	updateTransform();
}

void Shape::translateTo(vec3 newPos)
{
	vec3 translationVector = newPos - m_center;
	m_translation = glm::translate(mat4(1.0f), translationVector);
	updateTransform();
}

void Shape::translate(vec3 velocity)
{
	m_center += velocity;
	m_translation = glm::translate(m_translation, velocity);
	updateTransform();
}

const float Shape::getVerticesSize() const
{
	return this->m_vertices.size() * sizeof(float);
}

const mat4 Shape::getTransform() const
{
	return this->m_transform;
}

const GLuint Shape::getNumVertices() const
{
	return this->m_numVertices;
}

const GLuint Shape::getVAO() const
{
	return this->VAO;
}

const GLuint Shape::getEBO() const
{
	return this->EBO;
}

const GLuint Shape::getVBO() const
{
	return this->VBO;
}

void Shape::updateTransform()
{
	m_transform = m_translation * m_rotation * m_scale;
}