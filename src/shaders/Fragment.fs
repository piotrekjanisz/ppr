#version 150

in vec3 fragmentEye;

out vec4 fragColor;

void main(void)
{
 	vec3 normal;   
    normal.xy = gl_PointCoord.xy * vec2(2.0, -2.0) + vec2(-1.0, 1.0);

    float mag = dot(normal.xy, normal.xy);

    if (mag > 1.0)
        discard;

    normal.z = sqrt(1 - mag);
    
    vec3 light = normalize(vec3(5.0, 5.0, 10));
    vec3 eye = normalize(fragmentEye);
    
    float diffuseIntensity = clamp(max(dot(normal, light), 0.0), 0.0, 1.0);
    vec3 reflection = normalize(reflect(-light, normal));
    float specularIntensity = pow(clamp(max(dot(reflection, eye), 0.0), 0.0, 1.0), 20.0 );
    
    fragColor = vec4(0.0, 0.0, 0.0, 1.0) + vec4(0.1, 0.1, 0.1, 1.0) + vec4(1.0, 0.0, 0.0, 1.0)*diffuseIntensity + vec4(1.0, 0.9, 0.9, 1.0)*specularIntensity;
}
