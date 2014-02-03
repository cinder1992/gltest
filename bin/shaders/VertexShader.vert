#version 330 core
#extension GL_ARB_explicit_attrib_location: enable

precision highp float;
in vec3 vertexPosition_modelspace;
uniform mat4 MVP;
uniform mat4 ModelMatrix;
out vec4 VertPosInWorldSpace;

void main() {
  vec4 v = vec4(vertexPosition_modelspace,1);
  gl_Position = MVP * v;
  VertPosInWorldSpace = ModelMatrix * v;
}
