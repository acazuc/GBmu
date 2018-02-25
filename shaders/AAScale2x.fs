#version 330

in vec2 UV;

uniform sampler2D image;

layout(location = 0) out vec4 frag_color;

vec4 Scale2x(vec2 texCoord)
{
	vec2 textureDimensions = vec2(160, 144);
	// o = offset, the width of a pixel
	vec2 o = 1.0 / textureDimensions;
	// texel arrangement
	// A B C
	// D E F
	// G H I
	vec4 A = texture(image, texCoord + vec2( -o.x,  o.y));
	vec4 B = texture(image, texCoord + vec2(    0,  o.y));
	vec4 C = texture(image, texCoord + vec2(  o.x,  o.y));
	vec4 D = texture(image, texCoord + vec2( -o.x,    0));
	vec4 E = texture(image, texCoord + vec2(    0,    0));
	vec4 F = texture(image, texCoord + vec2(  o.x,    0));
	vec4 G = texture(image, texCoord + vec2( -o.x, -o.y));
	vec4 H = texture(image, texCoord + vec2(    0, -o.y));
	vec4 I = texture(image, texCoord + vec2(  o.x, -o.y));
	vec2 p = texCoord * textureDimensions;
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
		else // Bottom left
			return D == H && D != B && H != F ? D : E;
	}
}

vec4 AAScale2x(vec2 texCoord)
{
	return mix(texture(image, texCoord), Scale2x(texCoord), 0.5);
}

void main()
{
	frag_color = AAScale2x(UV);
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
