#include <glad/glad.h>

#include "Shape.h"

Shape::Shape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) : m_vertices(vertices), m_indices(indices) {}

const std::vector<float>& Shape::getVertices() const
{
	return m_vertices;
}

const std::vector<unsigned int>& Shape::getIndices() const
{
	return m_indices;
}
