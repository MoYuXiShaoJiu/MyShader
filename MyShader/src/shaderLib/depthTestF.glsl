#version 330 core
out vec4 FragColor;

//in vec2 TexCoords;
//const float offset = 1.0 / 300.0;  

in vec3 Normal;
in vec3 Position;
uniform vec3 camPos;
uniform samplerCube skybox;

void main()
{    
   //vec3 I=normalize(Position-camPos);
   //vec3 R=reflect(I,normalize(Normal));
   //R.y=-R.y;
   //FragColor=vec4(texture(skybox,R).rgb,1.0);
    //FragColor = texture(texture1, TexCoords);
//    float ratio = 1.00 / 1.52;
//    vec3 I = normalize(Position - camPos);
//    vec3 R = refract(I, normalize(Normal), ratio);
//    FragColor = vec4(texture(skybox, R).rgb, 1.0);
        //FragColor = vec4£¨0.6,0.2,0.5,1.0£©;
        FragColor=vec4(0.6,0.2,0.5,1.0);
}