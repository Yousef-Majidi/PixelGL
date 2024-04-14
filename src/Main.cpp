#include "App/App.h"

int main()
{
	const char* vertexShader = "src/Shader/shader.vs";
	const char* fragmentShader = "src/Shader/shader.fs";
	const char* geometryShader = "src/Shader/shader.gs";
	PixelGL::App::App app(1200, 800, vertexShader, fragmentShader, nullptr);
	app.run();
	return 0;
}