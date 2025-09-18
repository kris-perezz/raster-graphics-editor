#version 430 core

layout(location = 0) in vec2 a_position; 
layout(location = 1) in vec2 a_texCoords;


layout(location = 0) uniform vec2 mousePos;
layout(location = 2) uniform bool clear;
layout(location = 4) uniform float brushSize;
layout(location = 5) uniform vec2 canvasSize;

out vec2 v_texCoords;

void main()
{
    vec2 sizeNDC = (brushSize / canvasSize) * 2.0;
    vec2 mouseNDC = (mousePos / canvasSize) * 2.0 - 1.0;

    vec2 pos = clear ? a_position : (a_position * sizeNDC + mouseNDC);

    gl_Position = vec4(pos,0.0, 1.0);
    v_texCoords = a_texCoords;
}
