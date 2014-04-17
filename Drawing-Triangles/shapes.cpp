//
//
//run command g++ error.cpp -lglut -lGL -lGLEW -g


#include "initShaders.h"
using namespace std;
int counter=0;
int offset=0;
int size=0;

//vertexIDs
GLuint vaoID,vboID,eboID;;// the buffers that are going to be linked too
//vertices
GLfloat trianglearray[]={ 0.5f,-0.5f,
				0.0f,0.5f,
				-0.5f,-0.5f};// vertices that are drawn x,y, ...
				
GLfloat squarearray[]={ 0.5f,-0.5f,
                        0.5f,0.5f,
                        -0.5f,0.5f,
                        -0.5f,-0.5f};

GLfloat pentagonarray[]={ 0.0f,1.0f,
                          0.5f,0.5f,
                          0.5f,-0.5f,
                          -0.5f,-0.5f,
                          -0.5f,0.5f};

GLfloat hexagonarray[]={ -0.5f,0.0f,
                         -0.25f,0.5f,
                         0.25f,0.5f,
                         0.5f,0.0f,
                         0.25,-0.5f,
                         -0.25,-0.5f
                         };

void init(){
  glClear(GL_COLOR_BUFFER_BIT);//clears the screen
  
  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array

  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(trianglearray)+sizeof(squarearray)+sizeof(pentagonarray)+sizeof(hexagonarray), NULL, GL_STATIC_DRAW);//allocates the memory of the vertices
  
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(trianglearray), trianglearray);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(trianglearray), sizeof(squarearray), squarearray);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(trianglearray)+sizeof(squarearray), sizeof(pentagonarray), pentagonarray);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(trianglearray)+sizeof(squarearray)+sizeof(pentagonarray), sizeof(hexagonarray), hexagonarray);

 ShaderInfo shaders[]={//create the shader specified by my initshaders 
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
  { GL_NONE , NULL} 
  };

  initShaders(shaders);//creates shaders
  
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw
}

void drawscene(SDL_Window* screen){
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawArrays(GL_POLYGON,offset,size);
  SDL_GL_SwapWindow(screen);
}

void input(SDL_Window* screen){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
		  case SDL_QUIT:exit(0);break;
      case SDL_MOUSEBUTTONUP:
        switch(event.button.button){
          case SDL_BUTTON_LEFT:
            size=3+(counter%4);
            counter++;
            switch(size){
    	      case 3:offset=0;break;
    	      case 4:offset=3;break;
    	      case 5:offset=3+4;break;
    	      case 6:offset=3+4+5;break;
            }
            break;
          case SDL_BUTTON_RIGHT:exit(0);break;
        }
		  }
	  }
}

int main(int argc, char **argv){
	//SDL window and context management
	SDL_Window *window;
	
	if(SDL_Init(SDL_INIT_VIDEO)<0){//initilizes the SDL video subsystem
		fprintf(stderr,"Unable to create window: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);//die on error
	}
	
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
	
	
	glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "Unable to initalize GLEW");
    exit(EXIT_FAILURE);
  }
  
  //retruns what version of opengl and glsl your computer can use
  const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);
  fprintf(stderr,"Opengl glsl version %s\n", version);

  version=glGetString(GL_VERSION);
  fprintf(stderr,"Opengl version %s\n", version);
  
  init();
	

	while(1){
		drawscene(window);
		input(window);
		//SDL_GL_SwapBuffers();
	}
	
	SDL_GL_DeleteContext(glcontext);
  SDL_DestroyWindow(window);
  SDL_Quit();
 
  return 0;
}

