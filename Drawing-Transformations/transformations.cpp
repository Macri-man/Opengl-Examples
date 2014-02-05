#include "initShaders.h"
#include <cstdlib>
using namespace std;

GLuint vaoID,vboID;

GLfloat size=1;

GLfloat vertexarray[]={size,size,-size,
											 size,-size,-size,
                       -size,-size,-size,
                       -size,size,-size,
                       size,size,size,
                       size,-size,size,
                       -size,-size,size,
                       -size,size,size
                       };

GLfloat colorarray[]={1.0f,1.0f,1.0f,1.0f,
											0.5f,1.0f,1.0f,1.0f,
											1.0f,0.5f,1.0f,1.0f,
											1.0f,1.0f,0.5f,1.0f,
											1.0f,1.0f,1.0f,1.0f,
											0.5f,1.0f,1.0f,1.0f,
											1.0f,0.5f,1.0f,1.0f,
											1.0f,1.0f,0.5f,1.0f
											};
											
 GLfloat elems[]={0,1,2,3,7,4,5,6,
    							7,3,0,4,5,6,2,1,
    							0,1,5,4,7,3,2,6
                  };

void init(){
	 glEnable(GL_DEPTH_TEST);
	 glViewport(0, 0, 600, 600);
	
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
			yaw+=2;
			break;
			case 'd': case 'D':
			yaw-=2;
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
	
	//SDL window and context management
	SDL_Window *window;
	
	if(SDL_Init(SDL_INIT_VIDEO)<0){//initilizes the SDL video subsystem
		fprintf(stderr,"Unable to create window: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);//die on error
	}
	//get the version of opengl
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
	
	//create window
	window = SDL_CreateWindow(
		"Simple", //Window title
		SDL_WINDOWPOS_UNDEFINED, //initial x position
		SDL_WINDOWPOS_UNDEFINED, //initial y position
		500,							//width, in pixels
		500,							//height, in pixels
		SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN		//flags to be had
	);
	
	//check window creation
	if(window==NULL){
		fprintf(stderr,"Unable to create window: %s\n",SDL_GetError());
	}
	
	//creates opengl context associated with the window
	SDL_GLContext glcontext=SDL_GL_CreateContext(window);
	
	
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_BUTTON_RIGHT:exit(1);
		}
	}
	
	
	SDL_GL_DeleteContext(glcontext);
  SDL_DestroyWindow(window);
  SDL_Quit();
 
  return 0;
}
	
	/*
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
  */
}
	
