#version 430 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform bool hasTexture;

void main()
{
    if (hasTexture)
    {
        FragColor = texture(texture1, TexCoord);
    }
    else
    {
        FragColor = vec4(ourColor, 1.0);
    }
}