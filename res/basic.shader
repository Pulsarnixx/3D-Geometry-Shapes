#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textCoord;

out vec2 v_TexCoord;
uniform mat4 u_MVP;

void main()
{

gl_Position = u_MVP * position;
v_TexCoord = textCoord;

};

#shader fragment
#version 330 core

in vec2 v_TexCoord;
out vec4 color;

uniform sampler2D u_texture1;

void main()
{
    color = vec4(texture(u_texture1,v_TexCoord));
};

