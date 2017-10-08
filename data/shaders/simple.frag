#version 330 core

in vec3 v_color;

out vec4 out_color;

void main(void) {
  //out_color = vec4(v_color.x, v_color.y, v_color.z, 1.0);
  out_color = vec4(0.5, 0.5, 0.9, 1.0);
}
