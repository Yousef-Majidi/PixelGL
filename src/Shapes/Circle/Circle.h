#ifndef CIRCLE_H
#define CIRCLE_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <vector>
#include "../../Color/Color.h"
#include "../Shape.h"

using std::vector;
using glm::mat4;
using glm::vec3;

class Circle : public Shape
{
public:
	Circle() = delete;
	Circle(vec3 center, float size, Color color);

	void render() const override;
private:
	void generateVertices(vec3 center, float size, vec3 color) override;
	void generateBuffers(int bufferSize) override;
};
#endif // !CIRCLE_H
