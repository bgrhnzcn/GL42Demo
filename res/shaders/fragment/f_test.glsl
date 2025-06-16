#version 450 core

layout(location = 0) in vec4 position;
layout(location = 0) out vec4 color;

uniform float time;

float normf(float x, float min, float max)
{
	return (x - min) / (max - min);
}

void main()
{
	color = vec4(normf(position.x, -1, 1), normf(position.y, -1, 1), time, 1.0);
}
