// #define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <glm/ext/vector_float3.hpp>
#include <initializer_list>
#include <iostream>
#include "../../Color/Color.h"
#include "../../Shader/stb_image.h"
#include "../Shape.h"
#include "Cube.h"

namespace PixelGL
{
	namespace Shape
	{
		using
			glm::vec3,
			std::initializer_list,
			PixelGL::Color::Color;

		PixelGL::Shape::Cube::Cube(vec3 center, float width, float height, float depth, Color color, initializer_list<const char*> textures) : Shape(center, color)
		{
			int bytesToRead = 6;
			bool withTexture = textures.size() > 0;
			if (withTexture)
			{
				m_textures.resize(textures.size());
				m_selectedTexture = 0;
				bytesToRead = 8;
			}
			generateVertices(center, width, height, depth, color.getRGB());
			generateIndices();
			generateBuffers(bytesToRead);
			if (withTexture)
			{
				int i = 0;
				for (const char* texture : textures)
				{
					applyTexture(texture, i);
					i++;
				}
			}

		}

		void PixelGL::Shape::Cube::render() const
		{
			glEnable(GL_DEPTH_TEST);
			// glDepthFunc(GL_LESS);
			if (hasTextures())
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_textures.at(m_selectedTexture));
				glActiveTexture(GL_TEXTURE1);
				int nextTexture = 0;
				if (m_selectedTexture != m_textures.size() - 1)
				{
					nextTexture = m_selectedTexture + 1;
				}
				glBindTexture(GL_TEXTURE_2D, m_textures.at(nextTexture));
			}
			glBindVertexArray(VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glDrawElements(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, 0);

			// TODO: create a separate vbo and ebo for the edges and use GL_LINES to draw them separetly
			// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enable wireframe mode
			glDrawElements(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, 0);
			// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Disable wireframe mode

			// face culling
			// TODO: refactor into a separate function and the ability to set different parameters
			/*glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CW);*/
		}

		void Cube::generateVertices(glm::vec3 center, float size, glm::vec3 color)
		{
			std::cout << "Not implemented" << std::endl;
		}

		void PixelGL::Shape::Cube::generateVertices(vec3 center, float width, float height, float depth, vec3 color)
		{
			float halfWidth = width / 2;
			float halfHeight = height / 2;
			float halfDepth = depth / 2;
			if (hasTextures())
			{
				m_vertices =
				{
					// Front face
					center.x - halfWidth, center.y - halfHeight, center.z + halfDepth, color.x, color.y, color.z, 0.0f, 0.0f,
					center.x + halfWidth, center.y - halfHeight, center.z + halfDepth, color.x, color.y, color.z, 1.0f, 0.0f,
					center.x + halfWidth, center.y + halfHeight, center.z + halfDepth, color.x, color.y, color.z, 1.0f, 1.0f,
					center.x - halfWidth, center.y + halfHeight, center.z + halfDepth, color.x, color.y, color.z, 0.0f, 1.0f,
					// Back face
					center.x - halfWidth, center.y - halfHeight, center.z - halfDepth, color.x, color.y, color.z, 1.0f, 0.0f,
					center.x - halfWidth, center.y + halfHeight, center.z - halfDepth, color.x, color.y, color.z, 1.0f, 1.0f,
					center.x + halfWidth, center.y + halfHeight, center.z - halfDepth, color.x, color.y, color.z, 0.0f, 1.0f,
					center.x + halfWidth, center.y - halfHeight, center.z - halfDepth, color.x, color.y, color.z, 0.0f, 0.0f,
					// Top face
					center.x - halfWidth, center.y + halfHeight, center.z - halfDepth, color.x, color.y, color.z, 0.0f, 1.0f,
					center.x - halfWidth, center.y + halfHeight, center.z + halfDepth, color.x, color.y, color.z, 0.0f, 0.0f,
					center.x + halfWidth, center.y + halfHeight, center.z + halfDepth, color.x, color.y, color.z, 1.0f, 0.0f,
					center.x + halfWidth, center.y + halfHeight, center.z - halfDepth, color.x, color.y, color.z, 1.0f, 1.0f,
					// Bottom face
					center.x - halfWidth, center.y - halfHeight, center.z - halfDepth, color.x, color.y, color.z, 1.0f, 1.0f,
					center.x + halfWidth, center.y - halfHeight, center.z - halfDepth, color.x, color.y, color.z, 0.0f, 1.0f,
					center.x + halfWidth, center.y - halfHeight, center.z + halfDepth, color.x, color.y, color.z, 0.0f, 0.0f,
					center.x - halfWidth, center.y - halfHeight, center.z + halfDepth, color.x, color.y, color.z, 1.0f, 0.0f,
					// Right face
					center.x + halfWidth, center.y - halfHeight, center.z - halfDepth, color.x, color.y, color.z, 1.0f, 0.0f,
					center.x + halfWidth, center.y + halfHeight, center.z - halfDepth, color.x, color.y, color.z, 1.0f, 1.0f,
					center.x + halfWidth, center.y + halfHeight, center.z + halfDepth, color.x, color.y, color.z, 0.0f, 1.0f,
					center.x + halfWidth, center.y - halfHeight, center.z + halfDepth, color.x, color.y, color.z, 0.0f, 0.0f,
					// Left face
					center.x - halfWidth, center.y - halfHeight, center.z - halfDepth, color.x, color.y, color.z, 0.0f, 0.0f,
					center.x - halfWidth, center.y - halfHeight, center.z + halfDepth, color.x, color.y, color.z, 1.0f, 0.0f,
					center.x - halfWidth, center.y + halfHeight, center.z + halfDepth, color.x, color.y, color.z, 1.0f, 1.0f,
					center.x - halfWidth, center.y + halfHeight, center.z - halfDepth, color.x, color.y, color.z, 0.0f, 1.0f
				};
				return;
			}
			m_vertices =
			{
				// Front face
				center.x - halfWidth, center.y - halfHeight, center.z + halfDepth, color.x, color.y, color.z,
				center.x + halfWidth, center.y - halfHeight, center.z + halfDepth, color.x, color.y, color.z,
				center.x + halfWidth, center.y + halfHeight, center.z + halfDepth, color.x, color.y, color.z,
				center.x - halfWidth, center.y + halfHeight, center.z + halfDepth, color.x, color.y, color.z,
				// Back face
				center.x - halfWidth, center.y - halfHeight, center.z - halfDepth, color.x, color.y, color.z,
				center.x - halfWidth, center.y + halfHeight, center.z - halfDepth, color.x, color.y, color.z,
				center.x + halfWidth, center.y + halfHeight, center.z - halfDepth, color.x, color.y, color.z,
				center.x + halfWidth, center.y - halfHeight, center.z - halfDepth, color.x, color.y, color.z,
				// Top face
				center.x - halfWidth, center.y + halfHeight, center.z - halfDepth, color.x, color.y, color.z,
				center.x - halfWidth, center.y + halfHeight, center.z + halfDepth, color.x, color.y, color.z,
				center.x + halfWidth, center.y + halfHeight, center.z + halfDepth, color.x, color.y, color.z,
				center.x + halfWidth, center.y + halfHeight, center.z - halfDepth, color.x, color.y, color.z,
				// Bottom face
				center.x - halfWidth, center.y - halfHeight, center.z - halfDepth, color.x, color.y, color.z,
				center.x + halfWidth, center.y - halfHeight, center.z - halfDepth, color.x, color.y, color.z,
				center.x + halfWidth, center.y - halfHeight, center.z + halfDepth, color.x, color.y, color.z,
				center.x - halfWidth, center.y - halfHeight, center.z + halfDepth, color.x, color.y, color.z,
				// Right face
				center.x + halfWidth, center.y - halfHeight, center.z - halfDepth, color.x, color.y, color.z,
				center.x + halfWidth, center.y + halfHeight, center.z - halfDepth, color.x, color.y, color.z,
				center.x + halfWidth, center.y + halfHeight, center.z + halfDepth, color.x, color.y, color.z,
				center.x + halfWidth, center.y - halfHeight, center.z + halfDepth, color.x, color.y, color.z,
				// Left face
				center.x - halfWidth, center.y - halfHeight, center.z - halfDepth, color.x, color.y, color.z,
				center.x - halfWidth, center.y - halfHeight, center.z + halfDepth, color.x, color.y, color.z,
				center.x - halfWidth, center.y + halfHeight, center.z + halfDepth, color.x, color.y, color.z,
				center.x - halfWidth, center.y + halfHeight, center.z - halfDepth, color.x, color.y, color.z,
			};
		}

		void PixelGL::Shape::Cube::generateBuffers(unsigned int bytesToRead)
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, getVerticesSize(), m_vertices.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndicesSize(), m_indices.data(), GL_STATIC_DRAW);

			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, bytesToRead * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// color attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, bytesToRead * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			if (hasTextures())
			{
				// texture attribute
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, bytesToRead * sizeof(float), (void*)(6 * sizeof(float)));
				glEnableVertexAttribArray(2);
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void PixelGL::Shape::Cube::generateIndices()
		{
			m_indices =
			{
				0, 1, 2, 0, 2, 3,	// Front
				4, 5, 6, 4, 6, 7,	// Back
				8, 9, 10, 8, 10, 11,	// Top
				12, 13, 14, 12, 14, 15,	// Bottom
				16, 17, 18, 16, 18, 19,	// Right
				20, 21, 22, 20, 22, 23	// Left
			};
			m_numVertices = getIndicesSize() / sizeof(unsigned int);
		}

		void PixelGL::Shape::Cube::applyTexture(const char* texturePath, int textureIdx)
		{
			glGenTextures(1, &m_textures.at(textureIdx));
			glBindTexture(GL_TEXTURE_2D, m_textures.at(textureIdx));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_set_flip_vertically_on_load(true);
			int width, height, nrChannels;
			unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "Failed to load texture: " << texturePath << std::endl;
			}
			stbi_image_free(data);
		}

		const unsigned int PixelGL::Shape::Cube::getIndicesSize() const
		{
			return m_indices.size() * sizeof(unsigned int);
		}
	}
}

