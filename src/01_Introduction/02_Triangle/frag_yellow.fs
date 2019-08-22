#version 330 core
out vec4 FragColor;
in float cts;
void main()
{
    FragColor = vec4(0.9f, cts, 0.2f, 1.0f);
}
