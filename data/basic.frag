#version 430 core

layout(location = 0) uniform vec2 mousePos;
layout(location = 1) uniform vec4 brushColour;
layout(location = 2) uniform bool clear;
layout(location = 3) uniform vec4 canvasColour;

in vec2 v_texCoords;

out vec4 fragColour;

void main()
{
    if (clear) {
          fragColour = canvasColour;
    }
    else {
      
      vec2 center = vec2(0.5, 0.5);
      float delta = distance(v_texCoords, center);

      if ( delta <= 0.5) {
        fragColour = brushColour;
      }
      else {
        discard;
      }
    }

}
