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

	void generateVertices(glm::vec3 center, float size, glm::vec3 color);
	void generateIndices();
	void generateBuffers();
};
#endif // !RECTANGLE_H
