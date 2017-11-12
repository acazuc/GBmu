#ifndef SHADERS_H
# define SHADERS_H

char fragShader[] = {"#version 120\n\
\n\
varying vec2 UV;\n\
\n\
uniform sampler2D texture;\n\
\n\
void main()\n\
{\n\
	gl_FragColor = texture2D(texture, UV);\n\
}\n\
"};

char vertShader[] = {"#version 120\n\
\n\
attribute vec2 texCoords;\n\
attribute vec2 vertexes;\n\
\n\
varying vec2 UV;\n\
\n\
uniform mat4 MVP;\n\
\n\
void main()\n\
{\n\
	UV = texCoords;\n\
	gl_Position = MVP * vec4(vertexes, 0, 1);\n\
}\n\
"};

#endif
