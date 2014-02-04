#version 330 core

out vec4 color;
in vec4 VertPosInWorldSpace;

void main() {
  color = VertPosInWorldSpace / mat4(2.0); //poor-man's normalization
}
