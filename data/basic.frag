#version 430 core

layout(location = 0) out vec4 fragColour;

in vec2 v_texCoords;

uniform sampler2D tex;

void main()
{
  vec3 texColour = texture(tex, v_texCoords).rgb;
  fragColour = vec4(texColour, 1.0);
}
