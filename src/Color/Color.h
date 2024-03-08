#ifndef COLOR_H
#define COLOR_H

#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>

namespace PixelGL
{
	namespace Color
	{
		class Color
		{
		private:
			float m_red{}, m_green{}, m_blue{}, m_alpha{};
			glm::vec3 m_colors{};
			static float randomFloat();
		public:
			Color() = default;
			Color(float r, float g, float b, float a = 1.0f);
			static const Color RED;
			static const Color GREEN;
			static const Color BLUE;
			static const Color WHITE;
			static const Color BLACK;
			static const Color YELLOW;
			static const Color CYAN;
			static const Color MAGENTA;
			static glm::vec3 randomColor();

			glm::vec3 getRGB() const;
		};
	}
}
#endif // !COLOR_H