#version 120

varying vec2 UV;

uniform sampler2D image;

void main()
{
	gl_FragColor = vec4(texture2D(image, UV).rgb, 1);
}
