#ifndef CIRCLE_H
#define CIRCLE_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "../../Color/Color.h"

using std::vector;
using glm::mat4;
using glm::vec3;

class Circle
{
public:
	Circle() {};
	Circle(vec3 center, float size, Color color);
	~Circle();

	const GLuint GetVAO() const;
	const GLuint GetVBO() const;
	const GLuint getNumVertices() const;
	const mat4 getTransform() const;
	void render() const;
	void resetRotation();
	void resetPosition();
	void resetScale();
	void scale(float scaleFactor);
	void moveTo(vec3 newPos);
private:
	GLuint VAO{}, VBO{};
	GLuint m_numVertices{};
	GLuint m_size{};
	vector<float> m_vertices;
	vec3 m_center{};
	mat4 m_transform{};
	mat4 m_rotation{};
	mat4 m_translation{};
	mat4 m_scale{};
	Color m_color{};

	const float getVerticesSize() const;
	void generateVertices(vec3 center, vec3 color);
	void generateBuffers();
	void updateTransform();
};
#endif // !CIRCLE_H
