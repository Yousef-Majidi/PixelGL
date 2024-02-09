#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Rectangle
{
public:
	Rectangle() {};
	Rectangle(glm::vec3 center, float size, glm::vec3 color);
	~Rectangle();

	const GLuint getVAO() const;
	const GLuint getEBO() const;
	const GLuint getNumVertices() const;
private:
	GLuint VAO{}, VBO{}, EBO{};
	GLuint m_numVertices{};
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	glm::vec3 m_center{};

	const float getVerticesSize() const;
	const unsigned int getIndicesSize() const;
	void generateVertices(glm::vec3 center, float size, glm::vec3 color);
	void generateIndices();
	void generateBuffers();
};
#endif // !RECTANGLE_H
