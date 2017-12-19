
#version 330 core

uniform bool overrideColor;
in vec4 v_color;

out vec4 out_color;

void main(void) {
  if(overrideColor)
    out_color = vec4(0.3, 0.1, 0.8, 1.0);
  else
    out_color = vec4(v_color.x, v_color.y, v_color.z, v_color.a);
}
