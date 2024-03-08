#ifndef SHAPE_H
#define SHAPE_H

#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <vector>
#include "../Color/Color.h"

namespace PixelGL
{
	namespace Shape
	{
		class Shape
		{
		public:
			Shape() = delete;
			Shape(glm::vec3 center, PixelGL::Color::Color color);
			~Shape();

			virtual void render() const = 0;

			virtual void resetRotation();
			virtual void resetPosition();
			virtual void resetScale();
			virtual void rotate(float angle);
			virtual void scale(float scaleFactor);
			virtual void translateTo(glm::vec3 newPos);
			virtual void translate(glm::vec3 velocity);
			const void applyNextTexture();
			const void applyTexture(int textureIdx);
			const float getVerticesSize() const;
			const bool hasTextures() const;
			const glm::mat4 getTransform() const;
			const GLuint getNumVertices() const;
			const GLuint getVAO() const;
			const GLuint getEBO() const;
			const GLuint getVBO() const;

		protected:
			PixelGL::Color::Color m_color;
			glm::vec3 m_center;
			glm::mat4 m_transform;
			glm::mat4 m_rotation;
			glm::mat4 m_translation;
			glm::mat4 m_scale;
			GLuint m_numVertices{};
			GLuint VAO{}, VBO{}, EBO{};
			GLuint m_selectedTexture{};
			std::vector<float> m_vertices{};
			std::vector<GLuint> m_textures{};

			virtual void updateTransform();
			virtual void generateVertices(glm::vec3 center, float size, glm::vec3 color) = 0;
			virtual void generateBuffers(int bufferSize) = 0;
			virtual void applyTexture(const char* texture, int textureIdx) = 0;
		};
	}
}

#endif // !SHAPE_H