#version 130
in vec2 textCoord;

out vec4 FragColor;

uniform vec4 color;
uniform sampler2D texture1;

void main()
{
    // FragColor = color;
	FragColor = texture(texture1, textCoord) * color;
}
