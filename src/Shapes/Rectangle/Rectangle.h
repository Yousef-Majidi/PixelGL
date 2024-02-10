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
	const glm::mat4 getTransform() const;
	void resetRotation();
	void resetPosition();
	void resetScale();
	void rotate(float angle);
	void scale(float scaleFactor);
	void moveTo(glm::vec3 newPosition);
private:
	GLuint VAO{}, VBO{}, EBO{};
	GLuint m_numVertices{};
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	glm::vec3 m_center{};
	glm::mat4 m_transform{};
	glm::mat4 m_rotation{};
	glm::mat4 m_translation{};
	glm::mat4 m_scale{};

	const float getVerticesSize() const;
	const unsigned int getIndicesSize() const;
	void generateVertices(glm::vec3 center, float size, glm::vec3 color);
	void generateIndices();
	void generateBuffers();
	void updateTransform();
};
#endif // !RECTANGLE_H
