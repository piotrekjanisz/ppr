#version 150

uniform mat4 cameraRotation;

in vec3 fragmentEye;
in vec3 fragmentLight;
in float normalScale;
in mat4 normalTransform;

out vec4 fragColor;

void main(void)
{
 	vec4 normal;   
    normal.xy = gl_PointCoord.xy * vec2(2.0, -2.0) + vec2(-1.0, 1.0);
	//normal.xy = (gl_PointCoord.xy * 2.0f) - vec2(1.0f);

    float mag = dot(normal.xy, normal.xy);

    if (mag > 1.0f)
        discard;

    normal.z = sqrt(1.0f - mag);
    normal.w = 1.0f;
    //normal = cameraRotation * normal;
    //normal.xyz = normalize(normal.xyz * normalTransform);
    //normal.xyz = normalize((normalTransform * normal).xyz);
    
    vec3 light = -normalize(fragmentLight);
    vec3 eye = normalize(fragmentEye);
    
    float diffuseIntensity = max(dot(normal.xyz, light), 0.0);
    //diffuseIntensity = clamp(diffuseIntensity, 0.0f, 1.0f);
    
    vec3 reflection = -normalize(reflect(light, normal.xyz));
    float specularIntensity = pow(clamp(max(dot(reflection, eye), 0.0), 0.0, 1.0), 20.0 );
    
    //fragColor = vec4(0.1, 0.1, 0.1, 1.0) + vec4(1.0, 0.0, 0.0, 1.0)*diffuseIntensity + vec4(1.0, 0.9, 0.9, 1.0)*specularIntensity;
    fragColor = vec4(0.1, 0.1, 0.1, 1.0) + vec4(1.0, 0.0, 0.0, 1.0)*diffuseIntensity;
    //float green = 0.5f * (dot(normal.xyz, light) + 1.0f);
    //fragColor = vec4(1.0f, green, 0.0f, 1.0f);
    //fragColor = vec4(0.5f * (light + (1.0f, 1.0f, 1.0f)), 1.0f);
}
