#version 460 core

out vec4 FragColor;

in vec3 vertex_color;  
in vec2 texture_coord;

// texture samplers
uniform sampler2D texture_wall;
uniform sampler2D texture_face;

uniform float mix_ratio;

void main()
{
    // Normal
    FragColor = 
        mix(texture(texture_wall, texture_coord), 
            texture(texture_face, texture_coord), mix_ratio);

    return;

    // 4 Faces
    FragColor = 
        mix(texture(texture_wall, texture_coord), 
            texture(texture_face, texture_coord * 2), mix_ratio); // changes on this line
   
    // Added color gradient
    FragColor = 
        mix(texture(texture_wall, texture_coord), 
            texture(texture_face, texture_coord), mix_ratio)
        * vec4(vertex_color, 1); // added this line

    // Flip face to other side:
    FragColor = 
        mix(texture(texture_wall, texture_coord), 
            texture(texture_face, texture_coord * vec2(-1,1)), mix_ratio); // changes on this line
}
