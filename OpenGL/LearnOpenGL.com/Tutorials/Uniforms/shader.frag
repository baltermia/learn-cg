#version 460 core

in vec4 vertex_color;
in vec3 uv;

out vec4 FragColor;
  
uniform float seconds;

void main()
{
    vec3 col = .5 + .5 * sin(seconds + uv.xyx / 2 + vec3(0,2,4));
    FragColor = vec4(col, 1);
}  