#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{   
    // float border = dot(normalize(FragPos-viewPos),normalize(Normal));
    //     FragColor = vec4(1-border,1-border,1-border,1.0);
    //     FragColor = vec4(1-border,1-border,1-border,1.0);
    // FragColor = vec4(normalize(Normal-normalize(FragPos-viewPos)),1.0f);
    FragColor = vec4(Normal,1.0f);
}
