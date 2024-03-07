#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <initializer_list>
#include <iostream>
#include "../../Color/Color.h"
#include "../../Shader/stb_image.h"
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

Rectangle::Rectangle(vec3 center, float height, float width, Color color, std::initializer_list<const char*> textures) : Shape(center, color)
{
	if (textures.size() > 0)
	{
		std::cout << "texture list size: " << textures.size() << std::endl;
		generateVertices(center, height, width, color.getRGB(), true);
		generateIndices();
		generateBuffers(8);
		for (const char* texture : textures)
			applyTexture(texture);
		return;
	}
	generateVertices(center, height, width, color.getRGB());
	generateIndices();
	generateBuffers(6);
}

void Rectangle::render() const
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
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

void Rectangle::generateVertices(vec3 center, float height, float width, vec3 color, bool withTexture)
{
	float halfHeight = height / 2.0f;
	float halfWidth = width / 2.0f;
	if (withTexture)
	{
		m_vertices =
		{
			center.x + halfWidth, center.y + halfHeight, center.z, color.r, color.g, color.b, 1.0f, 1.0f,	// top right
			center.x + halfWidth, center.y - halfHeight, center.z, color.r, color.g, color.b, 1.0f, 0.0f,	// bottom right
			center.x - halfWidth, center.y - halfHeight, center.z, color.r, color.g, color.b, 0.0f, 0.0f,	// bottom left
			center.x - halfWidth, center.y + halfHeight, center.z, color.r, color.g, color.b, 0.0f, 1.0f	// top left
		};
		return;
	}
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
	// texture attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, bufferSize * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

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

void Rectangle::applyTexture(const char* texture)
{
	// delete the previous texture
	glDeleteTextures(1, &m_texture);
	// generate texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture); // the texture object is applied with all the texture operations
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set GL_REPEAT as the wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture, &width, &height, &nrChannels, 0);
	// Generate mipmaps
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: " << texture << std::endl;
	}
	stbi_image_free(data);
}

const unsigned int Rectangle::getIndicesSize() const
{
	return m_indices.size() * sizeof(unsigned int);
}