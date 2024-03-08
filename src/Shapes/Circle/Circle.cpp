#include <cmath>
#include <glad/glad.h>
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <utility>
#include <vector>
#include "../../Color/Color.h"
#include "../Shape.h"
#include "Circle.h"

namespace PixelGL
{
	namespace Shape
	{
		using
			glm::vec3,
			std::vector,
			PixelGL::Color::Color;

		Circle::Circle(vec3 center, float size, Color color) : Shape(center, color)
		{
			generateVertices(center, size, color.getRGB());
			generateBuffers(6);
		}

		void Circle::render() const
		{
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLE_FAN, 0, m_numVertices);
			glBindVertexArray(0);
		}

		void Circle::generateVertices(vec3 center, float size, vec3 color)
		{
			const GLuint numVertices = 360;
			float radius = std::max<float>(size, 0.05f);
			m_vertices.reserve(static_cast<vector<float, std::allocator<float>>::size_type>(numVertices) * 6);
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

		void Circle::generateBuffers(int bufferSize)
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, getVerticesSize(), m_vertices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, bufferSize * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, bufferSize * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

	}
}