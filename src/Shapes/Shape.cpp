#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "../Color/Color.h"
#include "../DeltaTime/DeltaTime.h"
#include "Shape.h"

namespace PixelGL
{
	namespace Shape
	{
		using
			glm::vec3,
			glm::mat4,
			PixelGL::Color::Color;

		Shape::Shape(vec3 center, Color color) : m_center(center), m_color(color)
		{
			m_transform = mat4{ 1.0f };
			m_rotation = mat4{ 1.0f };
			m_translation = glm::translate(mat4{ 1.0f }, center);
			m_scale = mat4{ 1.0f };
			updateTransform();
			std::cout << "Shape loaded at address: " << this << " with selected texture: " << m_selectedTexture << std::endl;
		}

		Shape::~Shape()
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
			for (GLuint texture : m_textures)
			{
				glDeleteTextures(1, &texture);
			}
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

		const void Shape::applyNextTexture()
		{
			if (!m_textures.empty())
			{
				std::cout << "applying texture for shape at address: " << this << std::endl;
				(m_selectedTexture < m_textures.size() - 1) ? m_selectedTexture++ : m_selectedTexture = 0;
				std::cout << "applied texture: " << m_selectedTexture << std::endl;
			}
		}

		const void Shape::applyTexture(int textureIdx)
		{
			if (textureIdx < m_textures.size())
			{
				std::cout << "applying texture for shape at address: " << this << std::endl;
				m_selectedTexture = textureIdx;
				std::cout << "applied texture: " << m_selectedTexture << std::endl;
			}
		}

		const float Shape::getVerticesSize() const
		{
			return m_vertices.size() * sizeof(float);
		}

		const bool Shape::hasTextures() const
		{
			return m_textures.size() > 0;
		}

		const mat4 Shape::getTransform() const
		{
			return m_transform;
		}

		const GLuint Shape::getNumVertices() const
		{
			return m_numVertices;
		}

		const GLuint Shape::getVAO() const
		{
			return VAO;
		}

		const GLuint Shape::getEBO() const
		{
			return EBO;
		}

		const GLuint Shape::getVBO() const
		{
			return VBO;
		}

		void Shape::updateTransform()
		{
			m_transform = m_translation * m_rotation * m_scale;
		}
	}
}