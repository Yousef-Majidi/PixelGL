#include <cstdlib>
#include <glm/glm.hpp>
#include <iostream>
#include <time.h>
#include "Color.h"

using glm::vec3;

const vec3 Color::RED = newColor(1.0f, 0.0f, 0.0f);
const vec3 Color::GREEN = newColor(0.0f, 1.0f, 0.0f);
const vec3 Color::BLUE = newColor(0.0f, 0.0f, 1.0f);
const vec3 Color::WHITE = newColor(1.0f, 1.0f, 1.0f);
const vec3 Color::BLACK = newColor(0.0f, 0.0f, 0.0f);
const vec3 Color::YELLOW = newColor(1.0f, 1.0f, 0.0f);
const vec3 Color::CYAN = newColor(0.0f, 1.0f, 1.0f);
const vec3 Color::MAGENTA = newColor(1.0f, 0.0f, 1.0f);

Color::Color(float r, float g, float b, float a) : m_red(r), m_green(g), m_blue(b), m_alpha(a)
{
	m_colors = vec3(r, g, b);
}

float Color::randomFloat()
{
	// TODO: Not implemented
	return float();
}

glm::vec3 Color::newColor(float r, float g, float b, float a)
{
	return vec3(r, g, b);
}

glm::vec3 Color::randomColor()
{
	// TODO: Not implemented
	return vec3();
}

vec3 Color::getRGB() const
{
	return this->m_colors;
}


