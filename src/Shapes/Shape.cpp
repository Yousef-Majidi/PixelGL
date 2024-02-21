//#include <glm/gtc/matrix_transform.hpp>
//#include "../Color/Color.h"
//#include "Shape.h"
//
//using glm::vec3;
//using glm::mat4;
//
//Shape::Shape(vec3 center, Color color) : m_transform(mat4(1.0f)), m_rotation(mat4(1.0f)), m_translation(mat4(1.0f)), m_scale(mat4(1.0f)), m_center(center), m_color(color)
//{
//	generateVertices(center, color.getRGB());
//	generateBuffers();
//}
//
//
//Shape::~Shape()
//{
//	// TODO: figure out later
//	// glDeleteVertexArrays(1, &this->VAO);
//	// glDeleteBuffers(1, &this->VBO);
//}
//
//const GLuint Shape::getVAO() const
//{
//	return this->VAO;
//}
//
//const GLuint Shape::getVBO() const
//{
//	return this->VBO;
//}
//
//const mat4 Shape::getTransform() const
//{
//	return this->m_transform;
//}
//
//void Shape::resetRotation()
//{
//	this->m_rotation = mat4(1.0f);
//	updateTransform();
//}
//
//void Shape::resetPosition()
//{
//	this->m_translation = mat4(1.0f);
//	updateTransform();
//}
//
//void Shape::ResetScale()
//{
//	this->m_scale = mat4(1.0f);
//	updateTransform();
//}
//
//void Shape::rotate(float angle)
//{
//	mat4 translate = glm::translate(mat4(1.0f), -m_center);
//	mat4 rotate = glm::rotate(mat4(1.0f), glm::radians(angle), vec3(0.0f, 0.0f, 1.0f));
//	mat4 translateBack = glm::translate(mat4(1.0f), m_center);
//	m_rotation = translateBack * rotate * translate * m_rotation;
//	updateTransform();
//}
//
//void Shape::scale(float scaleFactor)
//{
//	mat4 translate = glm::translate(mat4(1.0f), -m_center);
//	mat4 scale = glm::scale(mat4(1.0f), vec3(scaleFactor, scaleFactor, scaleFactor));
//	mat4 translateBack = glm::translate(mat4(1.0f), m_center);
//	m_scale = translateBack * scale * translate;
//	updateTransform();
//}
//
//void Shape::moveTo(vec3 newPos)
//{
//	vec3 translationVector = newPos - m_center;
//	m_translation = glm::translate(mat4(1.0f), translationVector);
//	updateTransform();
//}
//
//void Shape::updateTransform()
//{
//	m_transform = m_translation * m_rotation * m_scale;
//}
