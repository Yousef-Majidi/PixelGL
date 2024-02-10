#include "App/App.h"

int main()
{
    const char* vertexShader = "src/Shader/shader.vs";
    const char* fragmentShader = "src/Shader/shader.fs";
    App app(1200, 800, vertexShader, fragmentShader);
    app.run();
    return 0;
}
