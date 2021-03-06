#include "initShaders.h"
#include "vec.h"
#include <cstdlib>
#include <ctime>
using namespace std;

const int numpoints=4000;

GLuint vaoID, vboID;

void init(){
	
	vec2 points[numpoints];
	float k;
	float j;
	srand(time(0));
	
	for(int i=0;i<numpoints;i++){
		switch(i%4){
			case 0:
			j=((float) rand()/RAND_MAX);
			k=((float) rand()/RAND_MAX-1);
			//cout << " j: "<< j << " k: " << k << endl;
			points[i]=vec2(j,k);
			break;
			case 1:
			j=((float) rand()/RAND_MAX-1);
			k=((float) rand()/RAND_MAX-1);
			//cout << " j: "<< j << " k: " << k << endl;
			points[i]=vec2(j,k);
			break;
			case 2:
			j=((float) rand()/RAND_MAX);
			k=((float) rand()/RAND_MAX);
			//cout << " j: "<< j << " k: " << k << endl;
			points[i]=vec2(j,k);
			break;
			case 3:
			j=((float) rand()/RAND_MAX-1);
			k=((float) rand()/RAND_MAX);
			//cout << " j: "<< j << " k: " << k << endl;
			points[i]=vec2(j,k);
			break;
			}
	}
	
	glGenVertexArrays(1,&vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(1,&vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(points),points,GL_STATIC_DRAW);
	
	
	ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
  { GL_NONE , NULL} 
  };
  
	initShaders(shaders);
	
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);
	
}

void points(){
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_POINTS,0,numpoints);
		glFlush();
}

void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    exit(0);
}

int main(int argc, char **argv){
	
	glutInit(&argc,argv);
	glutCreateWindow("dots");

	
	glewExperimental=GL_TRUE;
	if(glewInit()){
		fprintf(stderr,"unable to initialize GLEW");
		exit(EXIT_FAILURE);
	}
	
	glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);
 
  const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);
  fprintf(stderr,"Opengl glsl version %s\n", version);

  version=glGetString(GL_VERSION);
  fprintf(stderr,"Opengl version %s\n", version);

	init();
	
  glutDisplayFunc(points);
  glutMouseFunc(mousepress);
  glutMainLoop();
  return 0;
}

