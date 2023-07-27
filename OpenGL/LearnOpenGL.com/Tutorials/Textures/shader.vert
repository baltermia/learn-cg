#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 col;

out vec3 vertex_color;
out vec2 texture_coord;

void main()
{
    gl_Position = vec4(pos, 1.0);
    texture_coord = tex;
    vertex_color = col;
}