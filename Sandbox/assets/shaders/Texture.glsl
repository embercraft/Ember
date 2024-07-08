#type vertex

#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextCoord;

uniform mat4 u_ViewProjection;

out vec2 v_TextCoord;
out vec4 v_Color;

void main()
{
	v_Color = a_Color;
	v_TextCoord = a_TextCoord;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment

#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextCoord;
in vec4 v_Color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform float u_TilingFactor;

void main()
{
	// color = texture(u_Texture, v_TextCoord * u_TilingFactor) * u_Color;
	color = v_Color;
}
