#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>
#include <glad/glad.h>

class Rectangle
{
public:
	Rectangle() {};
	Rectangle(float x, float y, float z, float r, float g, float b, float a);
	~Rectangle();

	const std::vector<float>& getVertices() const;
	const std::vector<unsigned int>& getIndices() const;

	const float getVerticesSize() const;
	const unsigned int getIndicesSize() const;
	const GLuint getVAO() const;
	const GLuint getEBO() const;
	const GLuint getNumVertices() const;
private:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;

	GLuint VAO{}, VBO{}, EBO{};
	GLuint m_numVertices{};

	void generateVertices(float x, float y, float z, float r, float g, float b, float a);
	void generateIndices();
};
#endif // !RECTANGLE_H
