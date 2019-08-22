#version 330
layout (location = 0) in vec3 aPos;


out float cts;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    cts = aPos.x;
}
