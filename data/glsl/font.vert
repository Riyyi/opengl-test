#version 130
in vec4 postex; // <vec2 position, vec2 texture>

out vec2 textCoord;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(postex.xy, 0.0f, 1.0f);
    textCoord = postex.zw;
}
