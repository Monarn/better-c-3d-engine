#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 aColor;
out float z;

uniform vec2 screenDim;
uniform vec3 oPos;

void main()
{
	vec3 tld = aPos + oPos;
	vec2 projected = tld.xy;
	gl_Position = vec4(projected, 1 , 1);
	aColor = aCol;
	float z = tld.z;
}
