#ifndef SHAPE_H
#define SHAPE_H

#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <vector>
#include "../Color/Color.h"

using std::vector;
using glm::mat4;
using glm::vec3;

class Shape
{
public:
	Shape() = delete;
	Shape(vec3 center, Color color);
	~Shape();

	virtual void render() const = 0;

	virtual void resetRotation();
	virtual void resetPosition();
	virtual void resetScale();
	virtual void rotate(float angle);
	virtual void scale(float scaleFactor);
	virtual void translateTo(vec3 newPos);
	virtual void translate(vec3 velocity);
	const float getVerticesSize() const;
	const mat4 getTransform() const;
	const GLuint getNumVertices() const;
	const GLuint getVAO() const;
	const GLuint getEBO() const;
	const GLuint getVBO() const;

protected:
	Color m_color;
	vec3 m_center;
	mat4 m_transform;
	mat4 m_rotation;
	mat4 m_translation;
	mat4 m_scale;
	GLuint m_numVertices{};
	GLuint VAO{}, VBO{}, EBO{};
	vector<float> m_vertices{};

	virtual void updateTransform();
	virtual void generateVertices(vec3 center, float size, vec3 color) = 0;
	virtual void generateBuffers() = 0;
};
#endif // !SHAPE_H