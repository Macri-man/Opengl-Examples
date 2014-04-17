#version 130

in vec4 pass_color;
in vec2 pass_texcoord;

out vec4 out_color;

uniform sampler2D tex;

void main(){
  out_color=texture(tex,pass_texcoord);
}
