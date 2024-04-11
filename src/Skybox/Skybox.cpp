#include <glad/glad.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <initializer_list>
#include <iostream>
#include <vector>
#include "../Shader/shaderinit.h"
#include "../Shader/stb_image.h"
#include "Skybox.h"

namespace PixelGL
{
	namespace Skybox
	{

		using
			glm::vec3,
			glm::mat4,
			glm::mat3,
			std::vector,
			std::initializer_list,
			PixelGL::Shader::Shader;

		Skybox::Skybox(const char* vertexPath, const char* fragmentPath, initializer_list<const char*> textures)
		{
			m_textures.resize(1);
			generateVertices();
			generateBuffers(3);
			initializeShader(vertexPath, fragmentPath);
			loadCubeMap(textures);
		}

		Skybox::~Skybox()
		{}

		void Skybox::render(const mat4& view, const mat4& projection)
		{
			glDepthFunc(GL_LEQUAL);
			glBindVertexArray(VAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_textures.at(0));

			mat4 viewNoTranslation = mat4(mat3(view));
			m_shader.use();
			m_shader.setMat4("view", viewNoTranslation);
			m_shader.setMat4("projection", projection);

			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			glDepthFunc(GL_LESS);
		}

		Shader Skybox::getShader() const
		{
			return m_shader;
		}

		void Skybox::initializeShader(const char* vertexPath, const char* fragmentPath)
		{
			m_shader = Shader(vertexPath, fragmentPath);
		}

		void Skybox::generateVertices()
		{
			m_vertices =
			{
				-1.0f,  1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,

				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,

				-1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f, -1.0f,

				-1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f
			};
		}

		void Skybox::generateBuffers(unsigned int bytesToRead)
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, getVerticesSize(), m_vertices.data(), GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, bytesToRead * sizeof(float), (void*)0);
		}

		void Skybox::loadCubeMap(initializer_list<const char*> faces)
		{
			glGenTextures(1, &m_textures.at(0));
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_textures.at(0));

			int width, height, nrChannels, index{};
			stbi_set_flip_vertically_on_load(false);
			for (auto const face : faces)
			{
				unsigned char* data = stbi_load(face, &width, &height, &nrChannels, 0);
				if (data)
				{
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
				}
				else
				{
					std::cout << "Cubemap texture failed to load at path: " << face << std::endl;
					stbi_image_free(data);
				}
				index++;
			}

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		const unsigned int Skybox::getVerticesSize() const
		{
			return m_vertices.size() * sizeof(float);
		}
	}
}

