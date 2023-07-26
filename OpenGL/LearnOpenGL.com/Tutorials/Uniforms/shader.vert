#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
  
out vec4 vertex_color;
out vec3 uv;

uniform float seconds;

void main()
{
    float norm = sin(seconds) / 2;

    gl_Position = vec4(pos.xy + norm, pos.z, 1.0);
    vertex_color = vec4(col, 1.0);

    uv = pos;
}
