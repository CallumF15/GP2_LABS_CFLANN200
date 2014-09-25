//header files
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>

using namespace std;


//Variables go here.



#pragma region Variables

//Pointer to our SDL windows
SDL_Window *window;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

//other
bool running = true;

//SDL GL Context
SDL_GLContext glcontext = NULL;




#pragma endregion


//Function to initialise OpenGL
void initOpenGL()
{
	glcontext = SDL_GL_CreateContext(window);


	//Something went wrong in creating the context if it is still NULL
	if (!glcontext){
		cout << "ERROR creating openGL context" << SDL_GetError() << endl;
		
	}

	//Smooth shading
	glShadeModel(GL_SMOOTH);

	//Clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//clear the depth buffer to 1.0
	glClearDepth(1.0f);

	//enable depth testing
	glEnable(GL_DEPTH_TEST);

	//the depth test to use
	glDepthFunc(GL_LEQUAL);

	//turn on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

//Function to set/reset viewport
void setViewport(int width, int height){
	//screen ration
	GLfloat ratio;

	//make sure the height is always above 0
	if (height == 0){
		height = 1;
	}

	//calculate screen ration
	ratio = (GLfloat)width / (GLfloat)height;

	//Setup Viewport
	glViewport(0, 0, (GLsizei)width,(GLsizei)height);

	//Change to project matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Calculate the perspective matrix using the glu library functions
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	//switch to model view
	glMatrixMode(GL_MODELVIEW);

	//Reset using the identity matrix
	glLoadIdentity();
}




void InitWindow(int width, int height, bool fullscreen) {
	window = SDL_CreateWindow(
		"Lab1", //Window Title
		SDL_WINDOWPOS_CENTERED,		//x position centered
		SDL_WINDOWPOS_CENTERED,		//Y position centered
		width,						//Width in pixels
		height,						//Height in pixels
		SDL_WINDOW_OPENGL			//flags
		);
}


void CleanUp()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	SDL_GL_DeleteContext(glcontext);
}


int main(int argc, char * arg[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout << "ERROR: SDL_init" << SDL_GetError() << endl;

		return -1;
	}

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	//Call our InitOpenGL Function
	initOpenGL();
	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);


	CleanUp();

	SDL_Event event;


	while (running){
		while (SDL_PollEvent(&event)){

			//Get Event Type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
				//set our boolean which controls game loop to false
				running = false;
			}


		}
	}



	return 0;
}


