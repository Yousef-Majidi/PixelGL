#ifndef COLOR_H
#define COLOR_H
#include <glm/glm.hpp>

using glm::vec3;

class Color
{
private:
	float m_red{}, m_green{}, m_blue{}, m_alpha{};
	vec3 m_colors{};
	static float randomFloat();
public:
	Color() = default;
	Color(float r, float g, float b, float a);
	static const vec3 RED;
	static const vec3 GREEN;
	static const vec3 BLUE;
	static const vec3 WHITE;
	static const vec3 BLACK;
	static const vec3 YELLOW;
	static const vec3 CYAN;
	static const vec3 MAGENTA;
	static vec3 newColor(float r, float g, float b, float a = 1.0f);
	static vec3 randomColor();

	vec3 getColors() const;
};
#endif // !COLOR_H
