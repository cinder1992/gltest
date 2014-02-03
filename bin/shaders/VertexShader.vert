#version 330 core
#extension GL_ARB_explicit_attrib_location: enable

precision highp float;
layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 MVP;

void main() {
  vec4 v = vec4(vertexPosition_modelspace,1);
  gl_position = MVP * v;
}