#version 330

in vec2 UV;

uniform sampler2D image;

layout(location = 0) out vec3 frag_color;

void main()
{
	frag_color = texture(image, UV).rgb;
}
