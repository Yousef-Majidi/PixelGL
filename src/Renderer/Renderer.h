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
			void initializeShader(const char*, const char*);

		private:
			PixelGL::Shader::Shader m_shader{};
		};
	}
}
#endif // !RENDERER_H