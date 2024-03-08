#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <initializer_list>
#include <vector>
#include "../../Color/Color.h"
#include "../Shape.h"

namespace PixelGL
{
	namespace Shape
	{
		class Rectangle : public Shape
		{
		public:
			Rectangle() = delete;
			Rectangle(glm::vec3 center, float size, PixelGL::Color::Color color);

			Rectangle(glm::vec3 center, float height, float width, PixelGL::Color::Color color, std::initializer_list<const char*> textures = {});

			void render() const override;
		private:
			std::vector<unsigned int> m_indices;

			void generateVertices(glm::vec3 center, float size, glm::vec3 color) override;
			void generateVertices(glm::vec3 center, float height, float width, glm::vec3 color);
			void generateBuffers(int bufferSize) override;
			void generateIndices();
			void applyTexture(const char* texture, int textureIdx);
			const unsigned int getIndicesSize() const;
		};
	}
}
#endif // !RECTANGLE_H