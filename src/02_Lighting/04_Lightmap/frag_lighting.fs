#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {     
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
}; 

uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform vec3 viewPos;

void main()
{
    // ambient

    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    
    // specular

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = -reflect(lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;//homework:(1-texture)

    // emission

    vec3 emission = texture(material.emission, TexCoords).rgb;

    // combined

    vec3 result = (ambient + diffuse + specular + emission) ;
    FragColor = vec4(result, 1.0);
}