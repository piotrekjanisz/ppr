#version 150
#extension GL_EXT_gpu_shader4 : enable
#extension GL_ARB_gpu_shader5 : enable

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec4 lightPosition;
uniform float pointSize;

in vec4 vertex;

out vec3 fLight;

void main(void)
{
	vec4 v = modelViewMatrix * vertex;

	fLight = normalize(lightPosition.xyz - v.xyz);

	float len = length(v);

	gl_PointSize = pointSize / len;
	
	gl_Position = projectionMatrix * v;	
}
