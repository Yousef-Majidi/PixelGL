#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include "../Shader/shaderinit.h"

namespace PixelGL
{
	namespace Renderer
	{
		class Renderer
		{
		public:
			Renderer();
			~Renderer();

			PixelGL::Shader::Shader getShader() const;
			void initializeGLFW();
			void initializeGLAD();
			void initializeShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath = nullptr);

		private:
			PixelGL::Shader::Shader m_shader{};
		};
	}
}
#endif // !RENDERER_H