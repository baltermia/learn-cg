#version 460 core

out vec4 FragColor;

in vec3 vertex_color;  
in vec2 texture_coord;

uniform sampler2D texture2d;

void main()
{
    FragColor = texture(texture2d, texture_coord) * vec4(vertex_color, 1);
}