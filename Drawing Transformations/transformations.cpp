#include "initShaders.h"
#include <cstdlib>
using namespace std;

GLuint vaoID,vboID;

Glfloat size=20;

GLfloat vertexarray[]={size,size,-size,
											 size,-size,-size,
                       -size,-size,-size,
                       -size,size,-size,
                       size,size,size,
                       size,-size,size,
                       -size,-size,size,
                       -size,size,size};

GLfloat colorarray[]={1.0f,1.0f,1.0f,1.0f,
											.5f,1.0f,1.0f,1.0f,
											1.0f,.5f,1.0f,1.0f,
											1.0f,1.0f,.5f,1.0f,
											1.0f,1.0f,1.0f,1.0f,
											.5f,1.0f,1.0f,1.0f,
											1.0f,.5f,1.0f,1.0f,
											1.0f,1.0f,.5f,1.0f,
											};
											
 GLfloat elems[]={0,1,2,3,7,4,5,6,
    							7,3,0,4,5,6,2,1,
    							0,1,5,4,7,3,2,6
                  };

void init(){
	
	glGenVertexArrays(1,&vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(1,&vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexarray),vertexarray,GL_STATIC_DRAW);
	
	ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"},
  { GL_FRAGMENT_SHADER , "fragmentshader.glsl"}, 
  { GL_NONE , NULL} 
  };
		
  initShaders(shaders);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawElements(GL_POLYGON,24,GL_FLOAT,NULL);
	glFlush();
}

void keypress(unsigned char key,int x,int y){
		switch(key){
			case 'w': case 'W':
			pit+=2;
			break;
			case 's': case 'S':
			pit-=2;
			break;
			case 'a': case 'A':
			yaw++=2;
			break;
			case 'd': case 'D':
			yaw--=2;
			break;
			case 'i': case 'I':
			cubeTran.x+=2;
			break;
			case 'k': case 'K':
			cubeTran.x-=2;
			break;
			case 'j': case 'J':
			cubeTran.y+=2;
			break;
			case 'l': case 'L':
			cubeTran.y-=2;
			break;
		}
}

void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    exit(0);
}


int main(int argc, char **argv){

	glViewport(0, 0, 600, 600);
	
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
  
	init();
	
  glutDisplayFunc(display);//displays callback draws the shapes
  glutMouseFunc(mousepress);//control callback specifies the mouse controls
  glutKeyboardFunc(keypress);//control callback specifies the mouse controls
  glutMainLoop();//sets opengl state in a neverending loop
  return 0;
}
	
