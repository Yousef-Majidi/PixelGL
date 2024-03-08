#ifndef DELTA_TIME_H
#define DELTA_TIME_H

namespace PixelGL
{
	class DeltaTime
	{
	public:
		DeltaTime(const DeltaTime&) = delete;
		DeltaTime& operator=(const DeltaTime&) = delete;

		static DeltaTime& getInstance();
		void update();
		float getDeltaTime() const;
		float getFPS() const;

	private:
		DeltaTime() : m_deltaTime(0.0f), m_lastFrame(0.0f) {}
		float m_deltaTime;
		float m_lastFrame;
	};
}
#endif // !DELTA_TIME_H


