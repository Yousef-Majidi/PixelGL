#include "Rectangle.h"

//Rectangle::Rectangle(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) : m_vertices(vertices), m_indices(indices) {}

Rectangle::Rectangle(float x, float y, float z, float r, float g, float b, float a)
{
	generateVertices(x, y, z, r, g, b, a);
	generateIndices();
}

const std::vector<float>& Rectangle::getVertices() const
{
	return this->m_vertices;
}

const std::vector<unsigned int>& Rectangle::getIndices() const
{
	return this->m_indices;
}

const float Rectangle::getVerticesSize() const
{
	return m_vertices.size() * sizeof(float);
}

const unsigned int Rectangle::getIndicesSize() const
{
	return m_indices.size() * sizeof(unsigned int);
}

void Rectangle::generateVertices(float x, float y, float z, float r, float g, float b, float a)
{
	m_vertices = {
		x, y, z, r, g, b, // top right
		x - 0.3f, y, z, r, g, b, // top left
		x - 0.3f, y - 0.3f, z, r, g, b, // bottom left
		x, y - 0.3f, z, r, g, b // bottom right
	};
}

void Rectangle::generateIndices()
{
	m_indices = {
		0, 1, 2,  // first Triangle
		2, 3, 0   // second Triangle
	};
}
