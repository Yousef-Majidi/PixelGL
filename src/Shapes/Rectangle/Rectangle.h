#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <vector>
#include "../../Color/Color.h"
#include "../Shape.h"

using std::vector;
using glm::mat4;
using glm::vec3;

class Rectangle : public Shape
{
public:
	Rectangle() = delete;
	Rectangle(vec3 center, float size, Color color);
	Rectangle(vec3 center, float height, float width, Color color);

	void render() const override;
private:
	vector<unsigned int> m_indices;

	void generateVertices(vec3 center, float size, vec3 color) override;
	void generateVertices(vec3 center, float height, float width, vec3 color);
	void generateBuffers() override;
	void generateIndices();
	const unsigned int getIndicesSize() const;
};
#endif // !RECTANGLE_H
