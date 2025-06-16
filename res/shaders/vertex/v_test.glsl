#version 450 core

layout(location = 0) in vec4 position;
layout(location = 0) out vec4 position_;

void main()
{
	gl_Position = position;
	position_ = position;
}
