#version 130
in vec3 aPos;
in vec2 aTextCoord;

out vec2 textCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// Vclip = Mprojection ⋅ Mview ⋅ Mmodel ⋅ Vlocal
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	textCoord = aTextCoord;
}
