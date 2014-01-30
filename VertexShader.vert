#version 330 core
#extension GL_ARB_explicit_attrib_location: enable

precision highp float;
layout(location = 0) in vec3 vertexPosition_modelspace;

void main() {
  gl_Position.xyz = vertexPosition_modelspace;
  gl_Position.w = 1.0f;
}
