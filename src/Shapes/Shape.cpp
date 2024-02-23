#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../Color/Color.h"
#include "Shape.h"

using glm::vec3;
using glm::mat4;

Shape::Shape(vec3 center, float size, Color color) : m_center(center), m_color(color)
{
	m_transform = mat4{ 1.0f };
	m_rotation = mat4{ 1.0f };
	m_translation = mat4{ 1.0f };
	m_scale = mat4{ 1.0f };
}

Shape::~Shape()
{
	// TODO: Figure this out later. Shapes are created in the wrong scope so get they get deleted before render and their buffers get deleted
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

void Shape::moveTo(vec3 newPos)
{
	vec3 translationVector = newPos - m_center;
	m_translation = glm::translate(mat4(1.0f), translationVector);
	updateTransform();
}

const GLuint Shape::getNumVertices() const
{
	return this->m_numVertices;
}

const mat4 Shape::getTransform() const
{
	return this->m_transform;
}

const float Shape::getVerticesSize() const
{
	return this->m_vertices.size() * sizeof(float);
}

void Shape::updateTransform()
{
	m_transform = m_translation * m_rotation * m_scale;
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
