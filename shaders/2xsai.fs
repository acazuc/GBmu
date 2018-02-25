#version 330

in vec2 UV;

uniform sampler2D image;

layout(location = 0) out vec3 frag_color;

void main()
{
	float dx = 0.25 / 160;
	float dy = 0.25 / 144;
	vec3 dt = vec3(1.0, 1.0, 1.0);
	vec4 yx = vec4(     dx,      dy,      -dx,      -dy);
	vec4 xh = vec4(3. * dx,      dy, -3. * dx,      -dy);
	vec4 yv = vec4(     dx, 3. * dy,      -dx, -3. * dy);
	vec4 ox = 2. * yx; 
	vec3 c11 = texture(image, UV        ).xyz;
	vec3 s00 = texture(image, UV + yx.zw).xyz;
	vec3 s20 = texture(image, UV + yx.xw).xyz;
	vec3 s22 = texture(image, UV + yx.xy).xyz;
	vec3 s02 = texture(image, UV + yx.zy).xyz;
	vec3 h00 = texture(image, UV + xh.zw).xyz;
	vec3 h20 = texture(image, UV + xh.xw).xyz;
	vec3 h22 = texture(image, UV + xh.xy).xyz;
	vec3 h02 = texture(image, UV + xh.zy).xyz;
	vec3 v00 = texture(image, UV + yv.zw).xyz;
	vec3 v20 = texture(image, UV + yv.xw).xyz;
	vec3 v22 = texture(image, UV + yv.xy).xyz;
	vec3 v02 = texture(image, UV + yv.zy).xyz;
	vec3 o00 = texture(image, UV + ox.zw).xyz;
	vec3 o20 = texture(image, UV + ox.xw).xyz;
	vec3 o22 = texture(image, UV + ox.xy).xyz;
	vec3 o02 = texture(image, UV + ox.zy).xyz;
	float m1 = 1.0 / (dot(abs(s00 - s22), dt) + 0.00001);
	float m2 = 1.0 / (dot(abs(s02 - s20), dt) + 0.00001);
	float h1 = 1.0 / (dot(abs(s00 - h22), dt) + 0.00001);
	float h2 = 1.0 / (dot(abs(s02 - h20), dt) + 0.00001);
	float h3 = 1.0 / (dot(abs(h00 - s22), dt) + 0.00001);
	float h4 = 1.0 / (dot(abs(h02 - s20), dt) + 0.00001);
	float v1 = 1.0 / (dot(abs(s00 - v22), dt) + 0.00001);
	float v2 = 1.0 / (dot(abs(s02 - v20), dt) + 0.00001);
	float v3 = 1.0 / (dot(abs(v00 - s22), dt) + 0.00001);
	float v4 = 1.0 / (dot(abs(v02 - s20), dt) + 0.00001);
	vec3 t1 = 0.5 * (m1 * (s00 + s22) + m2 * (s02 + s20)) / (m1 + m2);
	vec3 t2 = 0.5 * (h1 * (s00 + h22) + h2 * (s02 + h20) + h3 * (h00 + s22) + h4 * (h02 + s20)) / (h1 + h2 + h3 + h4);
	vec3 t3 = 0.5 * (v1 * (s00 + v22) + v2 * (s02 + v20) + v3 * (v00 + s22) + v4 * (v02 + s20)) / (v1 + v2 + v3 + v4);
	float k00 = dot(abs(o00 - c11), dt) + 0.00001;
	float k20 = dot(abs(o20 - c11), dt) + 0.00001;
	float k22 = dot(abs(o22 - c11), dt) + 0.00001;
	float k02 = dot(abs(o02 - c11), dt) + 0.00001;
	float kr1 = min(dot(abs(s00 - s22), dt), dot(abs(o00 - o22), dt));
	float kr2 = min(dot(abs(s02 - s20), dt), dot(abs(o20 - o02), dt));
	float w1 = (k22 < k00) ? 0.0 : kr2;
	float w2 = (k02 < k20) ? 0.0 : kr1;
	float w3 = (k00 < k22) ? 0.0 : kr2;
	float w4 = (k20 < k02) ? 0.0 : kr1; 
	c11 = (w1 * o00 + w2 * o20 + w3 * o22 + w4 * o02 + 0.001 * c11)/(w1 + w2 + w3 + w4 + 0.001);
	float k1 = 1.0 / (dot(abs(t1 - c11), dt) + 0.00001);
	float k2 = 1.0 / (dot(abs(t2 - c11), dt) + 0.00001);
	float k3 = 1.0 / (dot(abs(t3 - c11), dt) + 0.00001);
	frag_color = (k1 * t1 + k2 * t2 + k3 * t3) / (k1 + k2 + k3);
}

/* https://github.com/libretro/glsl-shaders/ */

/*
   Copyright (C) 2007 guest(r) - guest.r@gmail.com
   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
