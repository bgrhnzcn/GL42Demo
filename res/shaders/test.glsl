#ifdef COMPILING_VERTEX_SHADER
layout(location = 0) in vec4 position;
layout(location = 0) out vec4 position_;
void main()
{
	gl_Position = position;
	position_ = position;
}
#endif
#ifdef COMPILING_FRAGMENT_SHADER
layout(location = 0) in vec4 position;
layout(location = 0) out vec4 color;

float normf(float x, float min, float max)
{
	return (x - min) / (max - min);
}

void main()
{
	color = vec4(normf(position.x, -1, 1),
				 normf(position.y, -1, 1),
				 normf(position.z, 0, 1), 1.0);
}
#endif
