#version 330

in vec2 UV;

uniform sampler2D image;

layout(location = 0) out vec4 frag_color;

void main()
{
	frag_color = mix(vec4(1, 0, 0, 1), texture(image, UV), 0.5);
}
