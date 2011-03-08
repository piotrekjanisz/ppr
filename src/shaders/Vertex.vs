#version 150
#extension GL_EXT_gpu_shader4 : enable
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

uniform instanceData {
	//vec3 disp[1000];
	vec4 disp[1000];
};

in vec4 vertex;
in vec3 normal;

vec4 v;

out vec3 fragmentNormal;
out vec3 fragmentEye;

void main(void)
{
	v = vertex + disp[gl_InstanceID];
	//v = vertex + vec4(disp[gl_InstanceID], 1.0);
	fragmentNormal = (modelViewMatrix*vec4(normal, 0.0)).xyz;
	fragmentEye = (modelViewMatrix*v).xyz;
	fragmentEye = -normalize(fragmentEye);

	gl_Position = projectionMatrix*modelViewMatrix*v;
}
