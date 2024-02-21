#include "Circle.h"

Circle::Circle(vec3 center, float size, Color color) : m_center(center), m_size(size), m_color(color)
{
	generateVertices(center, color.getRGB());
	generateBuffers();
}

Circle::~Circle()
{
	// TODO: figure this out later
	/*glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);*/
}

const GLuint Circle::GetVAO() const
{
	return this->VAO;
}

const GLuint Circle::GetVBO() const
{
	return this->VBO;
}

const GLuint Circle::getNumVertices() const
{
	return this->m_numVertices;
}

const mat4 Circle::getTransform() const
{
	return this->m_transform;
}

void Circle::render() const
{
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, m_numVertices);
	glBindVertexArray(0);
}

void Circle::resetRotation()
{
	m_rotation = mat4(1.0f);
	updateTransform();
}

void Circle::resetPosition()
{
	m_translation = mat4(1.0f);
	updateTransform();
}

void Circle::resetScale()
{
	m_scale = mat4(1.0f);
	updateTransform();
}

void Circle::scale(float scaleFactor)
{
	mat4 translate = glm::translate(mat4(1.0f), -m_center);
	mat4 scale = glm::scale(mat4(1.0f), vec3(scaleFactor, scaleFactor, scaleFactor));
	mat4 translateBack = glm::translate(mat4(1.0f), m_center);
	m_scale = translateBack * scale * translate;
	updateTransform();
}

void Circle::moveTo(vec3 newPos)
{
	vec3 translationVector = newPos - m_center;
	m_translation = glm::translate(mat4(1.0f), translationVector);
	updateTransform();
}

const float Circle::getVerticesSize() const
{
	return m_vertices.size() * sizeof(float);
}

void Circle::generateVertices(vec3 center, vec3 color)
{
	const GLuint numVertices = 360;
	float radius = std::max<float>(m_size, 0.05f);
	for (GLuint i = 0; i < numVertices; i++)
	{
		float angle = 2.0f * 3.14159f * i / numVertices;
		float x = center.x + radius * std::cos(angle);
		float y = center.y + radius * std::sin(angle);
		m_vertices.push_back(x);
		m_vertices.push_back(y);
		m_vertices.push_back(0.0f);
		m_vertices.push_back(color.x);
		m_vertices.push_back(color.y);
		m_vertices.push_back(color.z);
	}
	m_numVertices = numVertices;
}

void Circle::generateBuffers()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, getVerticesSize(), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Circle::updateTransform()
{
	m_transform = m_translation * m_rotation * m_scale;
}
