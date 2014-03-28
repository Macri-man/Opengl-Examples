//
//
//run command g++ error.cpp -lglut -lGL -lGLEW -g


#include "initShaders.h"
using namespace std;
int counter=0;
int indexcounter=0;

//vertexIDs
GLuint vaoID, vboID;// the buffers that are going to be linked too
//vertices
GLfloat trianglearray[]={ 0.5f,-0.5f,
													0.0f,0.5f,
													-0.5f,-0.5f};// vertices that are drawn x,y, ...
				
GLfloat squarearray[]={ 0.5f,-0.5f,
                        0.5f,0.5f,
                        -0.5f,0.5f,
                        -0.5f,-0.5f};

GLfloat pentagonarray[]={ 0.0f,1.0f,
                          0.5f,-0.5f,
                          0.5f,0.5f,
                          -0.5f,0.5f,
                          -0.5f,-0.5f};

GLfloat hexagonarray[]={ 0.5f,0.0f,
                         0.25f,0.5f,
                         -0.25f,-0.5f,
                         -0.5f,0.0f,
                         -0.25,-0.5f,
                         0.25,0.5f
                         };
//indices of polygons
typedef struct {
  int offset;
  GLubyte indices;
} Polygonindices;

GLubyte triangleindices[3]={0,1,2};
GLubyte squareindices[4]={0,1,2,3};
GLubyte pentagonindices[5]={0,1,2,3,4};
GLubyte hexagonindices[6]={0,1,2,3,4,5};

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
  { GL_VERTEX_SHADER , "vertexshader1.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader1.glsl"},
  { GL_NONE , NULL} 
  };

  initShaders(shaders);//creates shaders
  
  
  
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw
}
/*
void drawscene(){
  switch(counter%2){//easy way to switch throw functions
    case 0:
      glutDisplayFunc(triangle1);
      glutPostRedisplay();//sets flags for opengl to redraw the display
      break;
    case 1:
      glutDisplayFunc(triangle2);
      glutPostRedisplay();
      break;
  }
}
*/
void drawscene(Polygonindices* indices){
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawElements(GL_POLYGON,3+(counter%3),GL_UNSIGNED_BYTE,);
  glFlush();
}

//this function create the interaction with the mouse
void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//right click closes the screen
    exit(0);
  else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){//left click changes the shape color
    cout << 3+(counter%4) << endl;
    counter++;
    drawscene();
  }
}

int main(int argc, char **argv){
	/*
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
	while(1){
		triangle1();
		SDL_GL_SwapBuffers();
	}
	
	SDL_GL_DeleteContext(glcontext);
  SDL_DestroyWindow(window);
  SDL_Quit();
 
  return 0;
}
*/
/*
	//GLFW window and context managment
	GLFWwindow* window;

    // Initialize the library 
    if(!glfwInit()){
    		fprintf(stderr,"unable to intilize GLFW");
        exit(EXIT_FAILURE);
    }

    // Create a windowed mode window and its OpenGL context 
    window = glfwCreateWindow(
    500, //width
    500, //height
    "Simple",//name
    NULL, //moniter
    NULL);//share
    //check to see if window created
    if (!window){
  			fprintf(stderr,"unable to open window");
        glfwTerminate();
       exit(EXIT_FAILURE);
    }

    // Make the window's context current 
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window 
    while (!glfwWindowShouldClose(window)){

        drawscene();
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){glfwSetWindowShouldClose(window, GL_TRUE);}
	
        // Swap front and back buffers 
        glfwSwapBuffers(window);

        // Poll for and process events 
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
*/

	//Freeglut window and context management	
  glutInit(&argc, argv);
  glutCreateWindow("Shapes");//creates the window with the specified name
  
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
  Polygonindices indices[]={
  {3,triangleindices[3]},
  {4,squareindices[4]},
  {5,pentagonindices[5]},
  {6,hexagonindices[6]},
  };
  
  glutDisplayFunc(drawscene(indices));//displays callback draws the shapes
  glutMouseFunc(mousepress);//control callback specifies the mouse controls
  glutMainLoop();//sets opengl state in a neverending loop
  return 0;
}

