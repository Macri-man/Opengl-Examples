#include "initShaders.h"
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

Gluint count=0;

GLuint vaoID,vboID;

GLfloat vertexarray[]={0.5f,-0.5f,0.0f,0.5f,0.5f,0.0f,-0.5f,-0.5f,0.0f,-0.5f,0.5f,0.0f};

void init(){
	
	glGenVertexArrays(1,&vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(1,&vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexarray),vertexarray,GL_STATIC_DRAW);
	
	 ShaderInfo shaders[]={
  	{ GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  	{ GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
  	{ GL_NONE , NULL} 
  	};

  	initShaders(shaders);
  	
  	glEnableVertexAttribArray(0);
  	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
  	
  	glm::mat4 temp;
    temp=glm::rotate(glm::mat4(),count,glm::vec3(0,0,1));
    
    int tempLoc = glGetUniformLocation(program, "viewMatrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
  	
  	glBindVertexArray(0);
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(2,vbo);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES,0,3);
	glFlush();
}

void keypress(unsigned char key,int w,int y){
		switch(key){
			case key=='w': case key=='W':
			count++;
			break;
			case key=='s': case key=='S':
			count++;
			break;
			case key=='a': case key=='A':
			count++;
			break;
			case key=='d': case key=='D':
			count++;
			break;
		}
}

void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    exit(0);
}


int main(int argc, char **argv){
	glutInit(&argc, argv);
  glutCreateWindow("transformations");//creates the window with the specified name
  
  //initializes glew
  glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "Unable to initalize GLEW");
    exit(EXIT_FAILURE);
  }
  
  glutInitContextVersion(4, 3);//specifies the version of opengl
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);//specifies what profile your using


  //retruns what version of opengl and glsl your computer can use
  const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);
  fprintf(stderr,"Opengl glsl version %s\n", version);

  version=glGetString(GL_VERSION);
  fprintf(stderr,"Opengl version %s\n", version);

  glutDisplayFunc(drawscene);//displays callback draws the shapes
  glutMouseFunc(mousepress);//control callback specifies the mouse controls
  glutMainLoop();//sets opengl state in a neverending loop
  return 0;
}
}
	
