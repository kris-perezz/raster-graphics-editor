#version 460 core

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D imgOutput;

layout(location = 0) uniform vec2 mousePos;

void main() {
    ivec2 texelCoord = ivec2(gl_GlobalInvocationID.xy);

    ivec2 size = imageSize(imgOutput);

    float brushSize = 8.0f;

    vec4 colour = imageLoad(imgOutput, texelCoord);

    if (mousePos.x != -1.0f) {
      float delta = length(vec2(texelCoord) - mousePos);

      if ( delta <= brushSize) {
        colour = vec4(1,1,1,1);
      }
      else {
        return;
      }
    }
	
    imageStore(imgOutput, texelCoord, colour);
}