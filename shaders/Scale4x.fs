#version 120

varying vec2 UV;

uniform sampler2D image;

vec4 Scale2x(vec2 texCoord)
{
	vec2 textureDimensions = vec2(160, 144);
	// o = offset, the width of a pixel
	vec2 o = 1.0 / textureDimensions;
	// texel arrangement
	// A B C
	// D E F
	// G H I
	vec4 A = texture2D(image, texCoord + vec2( -o.x,  o.y));
	vec4 B = texture2D(image, texCoord + vec2(    0,  o.y));
	vec4 C = texture2D(image, texCoord + vec2(  o.x,  o.y));
	vec4 D = texture2D(image, texCoord + vec2( -o.x,    0));
	vec4 E = texture2D(image, texCoord + vec2(    0,    0));
	vec4 F = texture2D(image, texCoord + vec2(  o.x,    0));
	vec4 G = texture2D(image, texCoord + vec2( -o.x, -o.y));
	vec4 H = texture2D(image, texCoord + vec2(    0, -o.y));
	vec4 I = texture2D(image, texCoord + vec2(  o.x, -o.y));
	vec2 p = texCoord * textureDimensions;
	// p = the position within a pixel [0...1]
	p = fract(p);
	if (p.x > .5)
	{
		if (p.y > .5) // Top right
			return B == F && B != D && F != H ? F : E;
		else // Bottom right
			return H == F && D != H && B != F ? F : E;
	}
	else
	{
		if (p.y > .5) // Top left
			return D == B && B != F && D != H ? D : E;
		else // Bottom left
			return D == H && D != B && H != F ? D : E;
	}
}

vec4 Scale4x(vec2 texCoord)
{
	vec2 textureDimensions = vec2(160, 144);
	// o = offset, the width of a pixel
	vec2 o = 1.0 / (textureDimensions * 2.);
	// texel arrangement
	// A B C
	// D E F
	// G H I
	vec4 A = Scale2x(texCoord + vec2( -o.x,  o.y));
	vec4 B = Scale2x(texCoord + vec2(    0,  o.y));
	vec4 C = Scale2x(texCoord + vec2(  o.x,  o.y));
	vec4 D = Scale2x(texCoord + vec2( -o.x,    0));
	vec4 E = Scale2x(texCoord + vec2(    0,    0));
	vec4 F = Scale2x(texCoord + vec2(  o.x,    0));
	vec4 G = Scale2x(texCoord + vec2( -o.x, -o.y));
	vec4 H = Scale2x(texCoord + vec2(    0, -o.y));
	vec4 I = Scale2x(texCoord + vec2(  o.x, -o.y));
	vec2 p = texCoord * textureDimensions * 2.;
	// p = the position within a pixel [0...1]
	p = fract(p);
	if (p.x > .5)
	{
		if (p.y > .5) // Top right
			return B == F && B != D && F != H ? F : E;
		else // Botton right
			return H == F && D != H && B != F ? F : E;
	}
	else
	{
		if (p.y > .5) // Top left
			return D == B && B != F && D != H ? D : E;
		else // Botton left
			return D == H && D != B && H != F ? D : E;
	}
}

void main()
{
	gl_FragColor = Scale4x(UV);
}

/* https://github.com/LIJI32/SameBoy */

/*
   MIT License

   Copyright (c) 2015-2018 Lior Halphon

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
 */
