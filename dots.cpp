#include "initShaders.h"
#include <cstdlib>
using namespace std;

const int numpoints=5000;

GLuint vaoID, vboID;
GLfloat vertexarray[]={}

void init(){
	
	vec2 points[numpoints];
	
	for(int i=0;i<numpoints,i++){
		int j=((float)rand()/1);
		int k=((float)rand()/1);
		points[i]=vec2(j,k);
	}
	glGenVertexArrays(1,&vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(1,&vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(points),points,GL_STATIC_DRAW);
	
	
	haderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
  { GL_NONE , NULL} 
  };
  
	initShader();
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*));
	
}

void display(){
		glClear(GL_COLOR_BUFFER_BIT);
		DrawArrays(GL_POINTS,0,2);
		glFlush();
}

void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//right click closes the screen
    exit(0);
}

