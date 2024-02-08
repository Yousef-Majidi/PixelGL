#include <glad/glad.h>

#include "Shape.h"

Shape::Shape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) : m_vertices(vertices), m_indices(indices) {}

const std::vector<float>& Shape::getVertices() const
{
	return this->m_vertices;
}

const std::vector<unsigned int>& Shape::getIndices() const
{
	return this->m_indices;
}

const float Shape::getVerticesSize() const
{
	return m_vertices.size() * sizeof(float);
}

const unsigned int Shape::getIndicesSize() const
{
	return m_indices.size() * sizeof(unsigned int);
}
