#type vertex

#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;
out float v_TilingFactor;

void main()
{
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;
    v_TilingFactor = a_TilingFactor;
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment

#version 330 core

layout(location = 0) out vec4 color;
layout(location = 1) out vec4 color2;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TilingFactor;
in float v_TexIndex;

uniform sampler2D u_TextureSlots[32];

void main()
{
    vec4 f_Texture;
    int f_TexIndex = int(v_TexIndex);

    switch (f_TexIndex) {
        case 0:  f_Texture = texture(u_TextureSlots[0],  v_TexCoord * v_TilingFactor); break;
        case 1:  f_Texture = texture(u_TextureSlots[1],  v_TexCoord * v_TilingFactor); break;
        case 2:  f_Texture = texture(u_TextureSlots[2],  v_TexCoord * v_TilingFactor); break;
        case 3:  f_Texture = texture(u_TextureSlots[3],  v_TexCoord * v_TilingFactor); break;
        case 4:  f_Texture = texture(u_TextureSlots[4],  v_TexCoord * v_TilingFactor); break;
        case 5:  f_Texture = texture(u_TextureSlots[5],  v_TexCoord * v_TilingFactor); break;
        case 6:  f_Texture = texture(u_TextureSlots[6],  v_TexCoord * v_TilingFactor); break;
        case 7:  f_Texture = texture(u_TextureSlots[7],  v_TexCoord * v_TilingFactor); break;
        case 8:  f_Texture = texture(u_TextureSlots[8],  v_TexCoord * v_TilingFactor); break;
        case 9:  f_Texture = texture(u_TextureSlots[9],  v_TexCoord * v_TilingFactor); break;
        case 10: f_Texture = texture(u_TextureSlots[10], v_TexCoord * v_TilingFactor); break;
        case 11: f_Texture = texture(u_TextureSlots[11], v_TexCoord * v_TilingFactor); break;
        case 12: f_Texture = texture(u_TextureSlots[12], v_TexCoord * v_TilingFactor); break;
        case 13: f_Texture = texture(u_TextureSlots[13], v_TexCoord * v_TilingFactor); break;
        case 14: f_Texture = texture(u_TextureSlots[14], v_TexCoord * v_TilingFactor); break;
        case 15: f_Texture = texture(u_TextureSlots[15], v_TexCoord * v_TilingFactor); break;
        case 16: f_Texture = texture(u_TextureSlots[16], v_TexCoord * v_TilingFactor); break;
        case 17: f_Texture = texture(u_TextureSlots[17], v_TexCoord * v_TilingFactor); break;
        case 18: f_Texture = texture(u_TextureSlots[18], v_TexCoord * v_TilingFactor); break;
        case 19: f_Texture = texture(u_TextureSlots[19], v_TexCoord * v_TilingFactor); break;
        case 20: f_Texture = texture(u_TextureSlots[20], v_TexCoord * v_TilingFactor); break;
        case 21: f_Texture = texture(u_TextureSlots[21], v_TexCoord * v_TilingFactor); break;
        case 22: f_Texture = texture(u_TextureSlots[22], v_TexCoord * v_TilingFactor); break;
        case 23: f_Texture = texture(u_TextureSlots[23], v_TexCoord * v_TilingFactor); break;
        case 24: f_Texture = texture(u_TextureSlots[24], v_TexCoord * v_TilingFactor); break;
        case 25: f_Texture = texture(u_TextureSlots[25], v_TexCoord * v_TilingFactor); break;
        case 26: f_Texture = texture(u_TextureSlots[26], v_TexCoord * v_TilingFactor); break;
        case 27: f_Texture = texture(u_TextureSlots[27], v_TexCoord * v_TilingFactor); break;
        case 28: f_Texture = texture(u_TextureSlots[28], v_TexCoord * v_TilingFactor); break;
        case 29: f_Texture = texture(u_TextureSlots[29], v_TexCoord * v_TilingFactor); break;
        case 30: f_Texture = texture(u_TextureSlots[30], v_TexCoord * v_TilingFactor); break;
        case 31: f_Texture = texture(u_TextureSlots[31], v_TexCoord * v_TilingFactor); break;
    }

    color = f_Texture * v_Color;

    color2 = vec4(0.9, 0.2, 0.1, 1.0);
}
