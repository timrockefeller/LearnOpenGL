#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;
uniform sampler2D texture_specular4;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{    

    
    FragColor = vec4(1,1,1,1.0);


    // vec3 result = texture(texture_diffuse1, TexCoords).rgb * 0.8;
    
    // vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(lightPos - FragPos);
    // vec3 viewDir = normalize(viewPos - FragPos);

    // vec3 reflectDir = -reflect(lightDir, norm);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // vec3 specular = spec * (texture(texture_specular1, TexCoords).rgb + texture(texture_specular2, TexCoords).rgb + texture(texture_specular3, TexCoords).rgb + texture(texture_specular4, TexCoords).rgb);
    // result += specular;

    // FragColor = vec4(result,1.0);
}
