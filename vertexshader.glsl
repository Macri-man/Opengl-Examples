#version 130


uniform mat4 viewMatrix;

in vec3 position;
void main(){
    gl_Position=viewMatrix*vec4(position, 1.0);
}

