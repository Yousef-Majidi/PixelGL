#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

namespace PixelGL
{
	namespace Camera
	{
		class Camera
		{
		public:
			Camera() = delete;
			Camera(glm::mat4 projection);
			~Camera() {};

			virtual void update() = 0;

			glm::mat4 getProjection();
			glm::mat4 getView();

		protected:
			glm::mat4 m_projection;
			glm::mat4 m_view;
		};
	}
}
#endif // !CAMERA_H