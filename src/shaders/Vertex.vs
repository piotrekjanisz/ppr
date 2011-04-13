#version 150
#extension GL_EXT_gpu_shader4 : enable
#extension GL_ARB_gpu_shader5 : enable
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec4 lightDirection;
uniform vec4 lightPosition;
uniform vec4 cameraPosition;
uniform vec4 cameraUp;

in vec4 vertex;

out vec3 fragmentEye;
out vec3 fragmentLight;
out mat4 normalTransform;

void main(void)
{
	vec4 v = modelViewMatrix * vertex;

	fragmentEye = -normalize(v.xyz);
	//fragmentLight = normalize(lightDirection.xyz);
	fragmentLight = -normalize(lightPosition.xyz - v.xyz);
	
	vec3 xAxis = normalize(cross(vec3(0.0f, 1.0f, 0.0f), fragmentEye));
	vec3 yAxis = normalize(cross(fragmentEye, xAxis));
	normalTransform[2] = vec4(normalize(vertex.xyz - cameraPosition.xyz), 0.0f);
	normalTransform[1] = vec4(normalize(cameraUp.xyz), 0.0f);
	normalTransform[0] = vec4(normalize(cross(normalTransform[1].xyz, normalTransform[2].xyz)), 0.0f);
	normalTransform[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	//normalTransform = inverse(normalTransform);

	float len = length(v);

	gl_PointSize = 500.0f / len;
	
	gl_Position = projectionMatrix * v;	
}
