#ifndef SHAPE_H
#define SHAPE_H

# include <vector>

class Shape
{
public:
	Shape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

	const std::vector<float>& getVertices() const;
	const std::vector<unsigned int>& getIndices() const;

	const float getVerticesSize() const;
	const unsigned int getIndicesSize() const;
private:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
};
#endif // !SHAPE_H
