#include <glm/ext/vector_float3.hpp>
#include "Color.h"

using glm::vec3;

const Color Color::RED = Color(1.0f, 0.0f, 0.0f);
const Color Color::GREEN = Color(0.0f, 1.0f, 0.0f);
const Color Color::BLUE = Color(0.0f, 0.0f, 1.0f);
const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);
const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f);
const Color Color::YELLOW = Color(1.0f, 1.0f, 0.0f);
const Color Color::CYAN = Color(0.0f, 1.0f, 1.0f);
const Color Color::MAGENTA = Color(1.0f, 0.0f, 1.0f);

Color::Color(float r, float g, float b, float a) : m_red(r), m_green(g), m_blue(b), m_alpha(a)
{
	m_colors = vec3(r, g, b);
}

float Color::randomFloat()
{
	// TODO: Not implemented
	return float();
}

vec3 Color::randomColor()
{
	// TODO: Not implemented
	return vec3();
}

vec3 Color::getRGB() const
{
	return this->m_colors;
}


