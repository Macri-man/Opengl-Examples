#version 130


uniform mat4 viewMatrix;
uniform mat4 Matrix;

in vec3 position;

void main(){
    gl_Position=Matrix*viewMatrix*vec4(position, 1.0);
}

