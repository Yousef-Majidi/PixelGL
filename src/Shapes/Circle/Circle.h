#ifndef CIRCLE_H
#define CIRCLE_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include "../../Color/Color.h"
#include "../Shape.h"

namespace PixelGL
{
	namespace Shape
	{
		class Circle : public Shape
		{
		public:
			Circle() = delete;
			Circle(glm::vec3 center, float size, PixelGL::Color::Color color);

			void render() const override;
		private:
			void generateVertices(glm::vec3 center, float size, glm::vec3 color) override;
			void generateBuffers(unsigned int bytesToRead) override;
		};
	}
}

#endif // !CIRCLE_H