#type vertex
#version 330 core

layout (location = 0) in vec4 a_Vertex; // <vec2 pos, vec2 tex>

uniform mat4 u_Projection;

out vec2 v_TexCoords;

void main()
{
    gl_Position = u_Projection * vec4(a_Vertex.xy, 0.0, 1.0);
    v_TexCoords = a_Vertex.zw;
}  

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoords;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}  
