#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../Camera.h"

namespace PixelGL
{
	namespace Camera
	{
		class PerspectiveCamera : public Camera
		{
		public:
			PerspectiveCamera() = delete;
			PerspectiveCamera(glm::mat4 projection, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float fov, float aspectRatio);
			~PerspectiveCamera() {};

			void update() override;
			const bool getFreeLook() const;
			void setFreeLook(bool freeLook);
			void freeLook(float x, float y);
			void zoom(float yoffset);
			void transform(glm::vec3 newPos);
			void setSpeed(int speed);

		private:
			glm::vec3 m_cameraPos;
			glm::vec3 m_cameraFront;
			glm::vec3 m_cameraUp;
			float m_fov;
			float m_yaw;
			float m_pitch;
			float m_aspectRatio;
			bool m_freeLook;
			bool m_firstMouseMovement;
			int m_cameraSpeed;

			void processMouseInput(float x, float y);
		};
	}
}

#endif // !PERSPECTIVE_CAMERA_H