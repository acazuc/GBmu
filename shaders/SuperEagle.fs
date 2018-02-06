#version 330

in vec2 UV;

uniform sampler2D image;

layout(location = 0) out vec4 frag_color;

vec3 dtt = vec3(65536, 255, 1);

float reduce(vec3 color)
{
	return dot(color, dtt);
}

int GET_RESULT(float A, float B, float C, float D)
{
	int x = 0; int y = 0; int r = 0;
	if (A == C) x+=1; else if (B == C) y+=1;
	if (A == D) x+=1; else if (B == D) y+=1;
	if (x <= 1) r+=1; 
	if (y <= 1) r-=1;
	return r;
}

vec4 SuperEagle(vec2 texCoord)
{
	float dx = 1. / 160;
	float dy = 1. / 144;
	vec2 fp = fract(texCoord * vec2(160, 144));
	// Reading the texels
	vec3 C0 = texture(image, texCoord + vec2(-dx     , -dy    )).xyz; 
	vec3 C1 = texture(image, texCoord + vec2(-dx     , 0      )).xyz;
	vec3 C2 = texture(image, texCoord + vec2( dx     , -dy    )).xyz;
	vec3 C3 = texture(image, texCoord + vec2(-dx     , 0      )).xyz;
	vec3 C4 = texture(image, texCoord).xyz;
	vec3 C5 = texture(image, texCoord + vec2( dx     , 0      )).xyz;
	vec3 C6 = texture(image, texCoord + vec2(-dx     , dy     )).xyz;
	vec3 C7 = texture(image, texCoord + vec2(  0     , dy     )).xyz;
	vec3 C8 = texture(image, texCoord + vec2( dx     , dy     )).xyz;
	vec3 D0 = texture(image, texCoord + vec2(-dx     , dy + dy)).xyz;
	vec3 D1 = texture(image, texCoord + vec2(  0     , dy + dy)).xyz;
	vec3 D2 = texture(image, texCoord + vec2( dx     , dy + dy)).xyz;
	vec3 D3 = texture(image, texCoord + vec2( dx + dx, -dy    )).xyz;
	vec3 D4 = texture(image, texCoord + vec2( dx + dx, 0      )).xyz;
	vec3 D5 = texture(image, texCoord + vec2( dx + dx, dy     )).xyz;
	vec3 D6 = texture(image, texCoord + vec2( dx + dx, dy + dy)).xyz;
	vec3 p00;
	vec3 p10;
	vec3 p01;
	vec3 p11;
	// reducing vec3 to float
	float c0 = reduce(C0);
	float c1 = reduce(C1);
	float c2 = reduce(C2);
	float c3 = reduce(C3);
	float c4 = reduce(C4);
	float c5 = reduce(C5);
	float c6 = reduce(C6);
	float c7 = reduce(C7);
	float c8 = reduce(C8);
	float d0 = reduce(D0);
	float d1 = reduce(D1);
	float d2 = reduce(D2);
	float d3 = reduce(D3);
	float d4 = reduce(D4);
	float d5 = reduce(D5);
	float d6 = reduce(D6);
	if (c4 != c8)
	{
		if (c7 == c5)
		{
			p01 = p10 = C7;
			if ((c6 == c7) || (c5 == c2))
				p00 = 0.25 * (3.0 * C7 + C4);
			else
				p00 = 0.5 * (C4 + C5);
			if ((c5 == d4) || (c7 == d1))
				p11 = 0.25 * (3.0 * C7 + C8);
			else
				p11 = 0.5 * (C7 + C8);
		}
		else
		{
			p11 = 0.125 * (6.0 * C8 + C7 + C5);
			p00 = 0.125 * (6.0 * C4 + C7 + C5);
			p10 = 0.125 * (6.0 * C7 + C4 + C8);
			p01 = 0.125 * (6.0 * C5 + C4 + C8);
		}
	}
	else
	{
		if (c7 != c5)
		{
			p11 = p00 = C4;
			if ((c1 == c4) || (c8 == d5))
				p01 = 0.25 * (3.0 * C4 + C5);
			else
				p01 = 0.5 * (C4 + C5);
			if ((c8 == d2) || (c3 == c4))
				p10 = 0.25 * (3.0 * C4 + C7);
			else
				p10 = 0.5 * (C7 + C8);
		}
		else
		{
			int r = 0;
			r += GET_RESULT(c5, c4, c6, d1);
			r += GET_RESULT(c5, c4, c3, c1);
			r += GET_RESULT(c5, c4, d2, d5);
			r += GET_RESULT(c5, c4, c2, d4);
			if (r > 0)
			{
				p01 = p10 = C7;
				p00 = p11 = 0.5 * (C4 + C5);
			}
			else if (r < 0)
			{
				p11 = p00 = C4;
				p01 = p10 = 0.5 * (C4 + C5);
			}
			else
			{
				p11 = p00 = C4;
				p01 = p10 = C7;
			}
		}
	}
	// Distributing the four products
	p10 = (fp.x < 0.50) ? (fp.y < 0.50 ? p00 : p10) : (fp.y < 0.50 ? p01 : p11);
	return vec4(p10, 1.0);
}

void main()
{
	frag_color = SuperEagle(UV);
}

/* https://github.com/libretro/slang-shaders */

/*  GET_RESULT function                            */
/*  Copyright (c) 1999-2001 by Derek Liauw Kie Fa  */
/*  License: GNU-GPL                               */

/*              SuperEagle code               */
/*  Copied from the Dosbox source code        */
/*  Copyright (C) 2002-2007  The DOSBox Team  */
/*  License: GNU-GPL                          */
/*  Adapted by guest(r) on 16.4.2007          */
