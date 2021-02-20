#version 130
in vec2 textCoord;

out vec4 fragColor;

uniform vec3 color;
uniform sampler2D texture1;

void main()
{    
	// Sample sets the alpha channel to either 0 / 1
	vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(texture1, textCoord).r);
	fragColor = vec4(color, 1.0f) * sampled;
}
