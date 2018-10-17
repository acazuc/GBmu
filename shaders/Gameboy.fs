#version 120

varying vec2 UV;

uniform sampler2D image;

void main()
{
	vec4 cmin = vec4(65. / 255., 65. / 255., 65. / 255., 1);
	vec4 cmax = vec4(196. / 255., 207. / 255., 161. / 255., 1);
	gl_FragColor = cmin + texture2D(image, UV) * (cmax - cmin);
}
