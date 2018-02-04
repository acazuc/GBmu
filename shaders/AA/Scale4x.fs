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
	frag_color = Scale4x(UV);
}

/* https://github.com/LIJI32/SameBoy */
