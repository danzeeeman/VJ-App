#version 120

uniform samplerCube envMap;
uniform float reflectivity;
varying vec3 N;
varying vec3 Normal;
varying vec3 reflectVec;

void main()
{
    vec4 cubeColor = textureCube(envMap, vec3(reflectVec.x, -reflectVec.y, reflectVec.z));
    gl_FragColor = cubeColor;
}
