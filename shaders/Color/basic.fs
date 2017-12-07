#version 450

in vec2 UV;

uniform sampler2D image;

out vec4 frag_color;

void main()
{
	frag_color = texture(image, UV);
}
