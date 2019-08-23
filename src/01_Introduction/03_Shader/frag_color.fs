#version 330 core
out vec4 FragColor;  
in vec3 ourColor;

uniform float lighting;

void main()
{
    FragColor = vec4(ourColor*lighting, 1.0);
}
