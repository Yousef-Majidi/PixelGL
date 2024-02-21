//#ifndef SHAPE_H
//#define SHAPE_H
//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "../Color/Color.h"
//
//using glm::mat4;
//using glm::vec3;
//
//class Shape
//{
//public:
//	Shape(vec3 center, Color color);
//	virtual ~Shape();
//
//	const GLuint getVAO() const;
//	const GLuint getVBO() const;
//	const mat4 getTransform() const;
//
//	virtual void render() const = 0;
//	virtual void resetRotation();
//	virtual void resetPosition();
//	virtual void ResetScale();
//	virtual void rotate(float angle);
//	virtual void scale(float scaleFactor);
//	virtual void moveTo(vec3 newPos);
//
//protected:
//	GLuint VAO;
//	GLuint VBO;
//	mat4 m_transform;
//	mat4 m_rotation;
//	mat4 m_translation;
//	mat4 m_scale;
//	vec3 m_center;
//	Color m_color;
//
//	virtual void generateVertices(vec3 center, vec3 color) = 0;
//	virtual void generateBuffers() = 0;
//	virtual void updateTransform();
//};
//
//#endif // !SHAPE_H
