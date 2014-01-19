#include "initShaders.h"
#include <cstdlib>
using namespace std;

GLuint vaoID,vboID;

GLfloat vertexarray[]={0.5f,-0.5f,0.0f,0.5f,0.5f,0.0f,-0.5f,-0.5f,0.0f,-0.5f,0.5f,0.0f};

void init(){
	
	glGenVertexArrays(1,&vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(1,&vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(points),points,GL_STATIC_DRAW);
}

void display(){

}

void keypress(){

}

void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    exit(0);
}


int main(int argc, char **argv){

}
	
