#version 120

attribute vec2 texCoords;
attribute vec2 vertexes;

varying vec2 UV;

uniform mat4 MVP;

void main()
{
	UV = texCoords;
	gl_Position = MVP * vec4(vertexes, 0, 1);
}
