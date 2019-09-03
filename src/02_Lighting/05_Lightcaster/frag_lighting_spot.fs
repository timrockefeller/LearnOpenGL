#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

// direct light
struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform vec3 viewPos;

void main() {

    vec3 lightDir = normalize(light.position - FragPos);
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // ambient

    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    vec3 result = ambient;


    // diffuse

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse =
        light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // specular

    vec3 reflectDir = -reflect(lightDir, norm);
    float spec =
        pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =
        light.specular * spec *
        texture(material.specular, TexCoords).rgb;  // homework:(1-texture)

    result += (diffuse + specular) * intensity;
    
    FragColor = vec4(result, 1.0);
}
