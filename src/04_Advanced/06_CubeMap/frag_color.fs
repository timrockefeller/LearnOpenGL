#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 Position;

uniform sampler2D texture1;
uniform samplerCube skybox;
uniform vec3 camPos;

uniform int ctrl;

void main()
{    
    
    vec3 I = normalize(Position - camPos);
    vec3 Rf = reflect(I, normalize(Normal)); 
    vec3 Rr = refract(I, normalize(Normal),	1.52f); 

    switch(ctrl){
        case 2:
        FragColor = vec4(texture(skybox, Rr).rgb, 1.0);  
        break;     
        case 1:
        default :
        FragColor = vec4(texture(skybox, Rf).rgb, 1.0);   
    }
}
