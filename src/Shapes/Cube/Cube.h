
#ifndef CUBE_H
#define CUBE_H

#include <glm/ext/vector_float3.hpp>
#include <initializer_list>
#include <vector>
#include "../../Color/Color.h"
#include "../Shape.h"

namespace PixelGL
{
	namespace Shape
	{
		class Cube : public Shape
		{
		public:
			Cube() = delete;
			Cube(glm::vec3 center, float width, float height, float depth, PixelGL::Color::Color color, std::initializer_list<const char*> textures = {});

			void render() const override;
		private:
			std::vector<unsigned int> m_indices;

			void generateVertices(glm::vec3 center, float size, glm::vec3 color);
			void generateVertices(glm::vec3 center, float width, float height, float depth, glm::vec3 color);
			void generateBuffers(unsigned int bytesToRead) override;
			void generateIndices();
			void applyTexture(const char* texturePath, int textureIdx);
			const unsigned int getIndicesSize() const;
		};
	}
}
#endif // !CUBE_H
