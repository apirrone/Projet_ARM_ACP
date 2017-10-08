#version 330 core

uniform mat4 proj_mat;
uniform mat4 view_mat;

in vec3 vtx_position;
in vec3 vtx_normal;
in vec3 vtx_color;

out vec3 v_color;

void main()
{
  gl_Position = proj_mat*vec4(vtx_position.x, vtx_position.y, vtx_position.z, 1.0);
  v_color = vtx_color;
}
