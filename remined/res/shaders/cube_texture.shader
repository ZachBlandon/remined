#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;
out vec3 v_TexCoord;
uniform mat4 u_PVM;

void main()
{
    gl_Position = u_PVM * vec4(pos, 1.0);
    v_TexCoord = pos;
};


#shader fragment
#version 330 core

in vec3 v_TexCoord;
out vec4 frag_color;

uniform samplerCube u_Texture;

void main()
{
    frag_color = texture(u_Texture, v_TexCoord);
};