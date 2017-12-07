#version 450

in vec2 texCoords;
in vec2 vertexes;

out vec2 UV;

uniform mat4 MVP;

void main()
{
	UV = texCoords;
	gl_Position = MVP * vec4(vertexes, 0, 1);
}
