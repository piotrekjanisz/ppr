#version 150
#extension GL_EXT_gpu_shader4 : enable
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

in vec4 vertex;

out vec3 fragmentEye;

void main(void)
{
	vec4 v = modelViewMatrix * vertex;

	fragmentEye = -normalize(v.xyz);

	gl_PointSize = 500.0f / length(v);
	
	gl_Position = projectionMatrix * v;	
}
