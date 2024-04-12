#version 460 core

out vec4 FragColor;
in vec3 aColor;
in float z;

void main()
{

	vec3 finalColor = aColor; 
	FragColor = vec4(finalColor, 1.0f);
}
