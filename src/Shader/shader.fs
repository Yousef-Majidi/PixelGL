#version 430 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform bool hasTexture;
uniform bool blend;

void main()
{
    if (hasTexture)
    {
        FragColor = texture(texture1, TexCoord);
        if (blend)
        {
            FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.3) * vec4(ourColor, 1.0);
        }
    }
    else
    {
        FragColor = vec4(ourColor, 1.0);
    }
}