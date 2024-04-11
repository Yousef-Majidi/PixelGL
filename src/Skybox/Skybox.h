#ifndef SKYBOX_H
#define SKYBOX_H

#include <glad/glad.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <initializer_list>
#include <vector>
#include "../Shader/shaderinit.h"

namespace PixelGL
{
	namespace Skybox
	{
		class Skybox
		{
		public:
			Skybox() {};
			Skybox(const char* vertexPath, const char* fragmentPath, std::initializer_list<const char*> textures);
			~Skybox();

			void render(const glm::mat4& view, const glm::mat4& projection);
			PixelGL::Shader::Shader getShader() const;

		private:
			PixelGL::Shader::Shader m_shader{};
			glm::vec3 m_center{};
			float m_size{};
			GLuint m_numVertices{};
			GLuint VAO{}, VBO{};
			std::vector<float> m_vertices{};
			std::vector<unsigned int> m_indices{};
			std::vector<GLuint> m_textures{};

			void initializeShader(const char* vertexPath, const char* fragmentPath);
			void generateVertices();
			void generateBuffers(unsigned int bytesToRead);
			void loadCubeMap(std::initializer_list<const char*> faces);
			const unsigned int getVerticesSize() const;
		};
	}
}


#endif // !SKYBOX_H
