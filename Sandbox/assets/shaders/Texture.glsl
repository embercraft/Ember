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

layout(location = 0) out vec4 o_FragColor;;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TilingFactor;
in float v_TexIndex;

uniform sampler2D u_TextureSlots[32];

void main()
{
    vec4 l_Texture;
    int l_TexIndex = int(v_TexIndex);

    switch (l_TexIndex) {
        case 0:  l_Texture = texture(u_TextureSlots[0],  v_TexCoord * v_TilingFactor); break;
        case 1:  l_Texture = texture(u_TextureSlots[1],  v_TexCoord * v_TilingFactor); break;
        case 2:  l_Texture = texture(u_TextureSlots[2],  v_TexCoord * v_TilingFactor); break;
        case 3:  l_Texture = texture(u_TextureSlots[3],  v_TexCoord * v_TilingFactor); break;
        case 4:  l_Texture = texture(u_TextureSlots[4],  v_TexCoord * v_TilingFactor); break;
        case 5:  l_Texture = texture(u_TextureSlots[5],  v_TexCoord * v_TilingFactor); break;
        case 6:  l_Texture = texture(u_TextureSlots[6],  v_TexCoord * v_TilingFactor); break;
        case 7:  l_Texture = texture(u_TextureSlots[7],  v_TexCoord * v_TilingFactor); break;
        case 8:  l_Texture = texture(u_TextureSlots[8],  v_TexCoord * v_TilingFactor); break;
        case 9:  l_Texture = texture(u_TextureSlots[9],  v_TexCoord * v_TilingFactor); break;
        case 10: l_Texture = texture(u_TextureSlots[10], v_TexCoord * v_TilingFactor); break;
        case 11: l_Texture = texture(u_TextureSlots[11], v_TexCoord * v_TilingFactor); break;
        case 12: l_Texture = texture(u_TextureSlots[12], v_TexCoord * v_TilingFactor); break;
        case 13: l_Texture = texture(u_TextureSlots[13], v_TexCoord * v_TilingFactor); break;
        case 14: l_Texture = texture(u_TextureSlots[14], v_TexCoord * v_TilingFactor); break;
        case 15: l_Texture = texture(u_TextureSlots[15], v_TexCoord * v_TilingFactor); break;
        case 16: l_Texture = texture(u_TextureSlots[16], v_TexCoord * v_TilingFactor); break;
        case 17: l_Texture = texture(u_TextureSlots[17], v_TexCoord * v_TilingFactor); break;
        case 18: l_Texture = texture(u_TextureSlots[18], v_TexCoord * v_TilingFactor); break;
        case 19: l_Texture = texture(u_TextureSlots[19], v_TexCoord * v_TilingFactor); break;
        case 20: l_Texture = texture(u_TextureSlots[20], v_TexCoord * v_TilingFactor); break;
        case 21: l_Texture = texture(u_TextureSlots[21], v_TexCoord * v_TilingFactor); break;
        case 22: l_Texture = texture(u_TextureSlots[22], v_TexCoord * v_TilingFactor); break;
        case 23: l_Texture = texture(u_TextureSlots[23], v_TexCoord * v_TilingFactor); break;
        case 24: l_Texture = texture(u_TextureSlots[24], v_TexCoord * v_TilingFactor); break;
        case 25: l_Texture = texture(u_TextureSlots[25], v_TexCoord * v_TilingFactor); break;
        case 26: l_Texture = texture(u_TextureSlots[26], v_TexCoord * v_TilingFactor); break;
        case 27: l_Texture = texture(u_TextureSlots[27], v_TexCoord * v_TilingFactor); break;
        case 28: l_Texture = texture(u_TextureSlots[28], v_TexCoord * v_TilingFactor); break;
        case 29: l_Texture = texture(u_TextureSlots[29], v_TexCoord * v_TilingFactor); break;
        case 30: l_Texture = texture(u_TextureSlots[30], v_TexCoord * v_TilingFactor); break;
        case 31: l_Texture = texture(u_TextureSlots[31], v_TexCoord * v_TilingFactor); break;
    }

    o_FragColor = l_Texture * v_Color;
}
