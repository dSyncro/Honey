#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in int a_TexIndex;
layout(location = 4) in vec2 a_Tiling;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;
out int v_TexIndex;
out vec2 v_Tiling;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_Tiling = a_Tiling;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in flat int v_TexIndex;
in vec2 v_Tiling;

uniform sampler2D u_Textures[32];

void main()
{
	// Dynamic Indexing does not work;
	vec4 tex;
	switch (v_TexIndex)
	{
		case  0: tex = texture(u_Textures[0], v_TexCoord * v_Tiling); break;
		case  1: tex = texture(u_Textures[1], v_TexCoord * v_Tiling); break;
		case  2: tex = texture(u_Textures[2], v_TexCoord * v_Tiling); break;
		case  3: tex = texture(u_Textures[3], v_TexCoord * v_Tiling); break;
		case  4: tex = texture(u_Textures[4], v_TexCoord * v_Tiling); break;
		case  5: tex = texture(u_Textures[5], v_TexCoord * v_Tiling); break;
		case  6: tex = texture(u_Textures[6], v_TexCoord * v_Tiling); break;
		case  7: tex = texture(u_Textures[7], v_TexCoord * v_Tiling); break;
		case  8: tex = texture(u_Textures[8], v_TexCoord * v_Tiling); break;
		case  9: tex = texture(u_Textures[9], v_TexCoord * v_Tiling); break;
		case 10: tex = texture(u_Textures[10], v_TexCoord * v_Tiling); break;
		case 11: tex = texture(u_Textures[11], v_TexCoord * v_Tiling); break;
		case 12: tex = texture(u_Textures[12], v_TexCoord * v_Tiling); break;
		case 13: tex = texture(u_Textures[13], v_TexCoord * v_Tiling); break;
		case 14: tex = texture(u_Textures[14], v_TexCoord * v_Tiling); break;
		case 15: tex = texture(u_Textures[15], v_TexCoord * v_Tiling); break;
		case 16: tex = texture(u_Textures[16], v_TexCoord * v_Tiling); break;
		case 17: tex = texture(u_Textures[17], v_TexCoord * v_Tiling); break;
		case 18: tex = texture(u_Textures[18], v_TexCoord * v_Tiling); break;
		case 19: tex = texture(u_Textures[19], v_TexCoord * v_Tiling); break;
		case 20: tex = texture(u_Textures[20], v_TexCoord * v_Tiling); break;
		case 21: tex = texture(u_Textures[21], v_TexCoord * v_Tiling); break;
		case 22: tex = texture(u_Textures[22], v_TexCoord * v_Tiling); break;
		case 23: tex = texture(u_Textures[23], v_TexCoord * v_Tiling); break;
		case 24: tex = texture(u_Textures[24], v_TexCoord * v_Tiling); break;
		case 25: tex = texture(u_Textures[25], v_TexCoord * v_Tiling); break;
		case 26: tex = texture(u_Textures[26], v_TexCoord * v_Tiling); break;
		case 27: tex = texture(u_Textures[27], v_TexCoord * v_Tiling); break;
		case 28: tex = texture(u_Textures[28], v_TexCoord * v_Tiling); break;
		case 29: tex = texture(u_Textures[29], v_TexCoord * v_Tiling); break;
		case 30: tex = texture(u_Textures[30], v_TexCoord * v_Tiling); break;
		case 31: tex = texture(u_Textures[31], v_TexCoord * v_Tiling); break;
	}

    vec4 sampled = vec4(1.0, 1.0, 1.0, tex.r);
    color = v_Color * sampled;
}  
