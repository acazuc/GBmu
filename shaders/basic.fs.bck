#version 130

varying vec2 UV;

uniform sampler2D texture;

void main()
{
	vec4 cmin = vec4(65. / 255., 65. / 255., 65. / 255., 1);
	vec4 cmax = vec4(196. / 255., 207. / 255., 161. / 255., 1);
	gl_FragColor = cmin + texture2D(texture, UV) * (cmax - cmin);
	/*vec2 delta = vec2(1. / 160., 1. / 144.);
	vec2 rel = vec2(mod(UV.x, delta.x), mod(UV.y, delta.y));
	vec2 tex = UV;
	rel = rel * vec2(160, 140);
	vec4 ctl = texture2D(texture, vec2(tex.x - delta.x, tex.y - delta.y));
	vec4 ctm = texture2D(texture, vec2(tex.x          , tex.y - delta.y));
	vec4 ctr = texture2D(texture, vec2(tex.x + delta.x, tex.y - delta.y));
	vec4 cml = texture2D(texture, vec2(tex.x - delta.x, tex.y          ));
	vec4 cmm = texture2D(texture, vec2(tex.x          , tex.y          ));
	vec4 cmr = texture2D(texture, vec2(tex.x + delta.x, tex.y          ));
	vec4 cbl = texture2D(texture, vec2(tex.x - delta.x, tex.y + delta.y));
	vec4 cbm = texture2D(texture, vec2(tex.x          , tex.y + delta.y));
	vec4 cbr = texture2D(texture, vec2(tex.x + delta.x, tex.y + delta.y));
	if (rel.x + rel.y <= .5) //top left
	{
		if (ctm == cml && cmm != ctl)
			gl_FragColor = ctm;
		else
			gl_FragColor = cmm;
	}
	else if (rel.x >= .5 && rel.x - .5 >= rel.y) // top right
	{
		if (ctm == cmr && cmm != ctr)
			gl_FragColor = ctm;
		else
			gl_FragColor = cmm;
	}
	else if (rel.y >= .5 && rel.y - .5 >= rel.x) // bottom left
	{
		if (cbm == cml && cmm != cbl)
			gl_FragColor = cbm;
		else
			gl_FragColor = cmm;
	}
	else if (rel.x >= .5 && rel.y >= .5 && 1. - rel.x + 1. - rel.y <= .5) // bottom right
	{
		if (cbm == cmr && cmm != cbr)
			gl_FragColor = cbm;
		else
			gl_FragColor = cmm;
	}
	else
	{
		gl_FragColor = cmm;
	}*/
}
