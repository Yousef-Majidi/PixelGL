#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>

class Rectangle
{
public:
	//Shape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
	Rectangle(float x, float y, float z, float r, float g, float b, float a);

	const std::vector<float>& getVertices() const;
	const std::vector<unsigned int>& getIndices() const;

	const float getVerticesSize() const;
	const unsigned int getIndicesSize() const;
private:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;

	void generateVertices(float x, float y, float z, float r, float g, float b, float a);
	void generateIndices();
};
#endif // !RECTANGLE_H
