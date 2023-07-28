#version 460 core

out vec4 FragColor;

in vec3 vertex_color;  
in vec2 texture_coord;

// texture samplers
uniform sampler2D texture_wall;
uniform sampler2D texture_face;

void main()
{
    FragColor = 
        mix(texture(texture_wall, texture_coord), 
            texture(texture_face, texture_coord), .2) 
        * vec4(vertex_color, 1);
}