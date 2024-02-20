#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "../../Color/Color.h"

using std::vector;
using glm::mat4;
using glm::vec3;

class Rectangle
{
public:
	Rectangle() {};
	Rectangle(glm::vec3 center, float size, Color color);
	~Rectangle();

	const GLuint getVAO() const;
	const GLuint getEBO() const;
	const GLuint getNumVertices() const;
	const mat4 getTransform() const;
	void render() const;
	void resetRotation();
	void resetPosition();
	void resetScale();
	void rotate(float angle);
	void scale(float scaleFactor);
	void moveTo(vec3 newPosition);
private:
	GLuint VAO{}, VBO{}, EBO{};
	GLuint m_numVertices{};
	vector<float> m_vertices;
	vector<unsigned int> m_indices;
	vec3 m_center{};
	mat4 m_transform{};
	mat4 m_rotation{};
	mat4 m_translation{};
	mat4 m_scale{};
	Color m_color{};

	const float getVerticesSize() const;
	const unsigned int getIndicesSize() const;
	void generateVertices(vec3 center, float size, vec3 color);
	void generateIndices();
	void generateBuffers();
	void updateTransform();
};
#endif // !RECTANGLE_H
