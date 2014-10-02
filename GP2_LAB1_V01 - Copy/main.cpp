//header files

#include <GL/glew.h> //note: this has to be above the opengl/sdl headers.
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>


using namespace std;


struct vertexPos
{
	float x, y;
	float r, g, b;
};


#pragma region Variables

//Pointer to our SDL windows
SDL_Window * window;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

//other
bool running = true;

//SDL GL Context
SDL_GLContext glcontext = NULL;

GLuint triangleVBO;

#pragma endregion



vertexPos pos[] = { { 2.0f, 1.0f, // x,y
0.5f, 0.0f, 1.0f }, //rgba
{ 2.0f, -1.0f,    	  //x,y
1.0f, 0.0f, 0.0f }, //rgba
{ 0.0f, -1.0f,		  // x,y
0.0f, 1.0f, 0.0f }  //rgba
};

float triangleData[] = { 
0.0f, 1.0f, 0.0f, // Top
-1.0f, -1.0f, 0.0f, // Bottom Left
1.0f, -1.0f, 0.0f }; //Bottom Right

//minor change


#pragma region Methods

void update()
{

}

void render()
{
	//Set the clear colour background
	glClearColor(0.9f, 0.9f, 0.9f, 0.3f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Make the new VBO active. Repeat here as a sanity check( may have changed 
	//since initialisation)
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

	//Establish its 3 coordinates per vertex with zero stride(space between elements) 
	//in array and contain floating point numbers
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	//Establish array contains vertices (not normals, colours, texture coords etc)
	glEnableClientState(GL_VERTEX_ARRAY);



	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);
	//Reset using the Indentity Matrix
	glLoadIdentity();
	//Translate to -5.0f on z-axis
	glTranslatef(0.0f, 0.0f, -5.0f);

	//Begin drawing triangles (standard triangle)
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f); //Colour of the vertices
	//glVertex3f(0.0f, 1.0f, 0.0f); // Top
	//glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left
	//glVertex3f(1.0f, -1.0f, 0.0f); // Bottom Right
	//glEnd();

	//Right-angled Triangle
	//glBegin(GL_TRIANGLES);
	//glColor3f(0.5f, 0.0f, 1.0f); //Colour of the vertices
	//glVertex3f(1.0f, 1.0f, 0.0f); // Top
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(1.0f, -1.0f, 0.0f); // Bottom Right
	//glEnd();

	//Mirrored Right-angled triangled
	//glBegin(GL_TRIANGLES);
	//glColor3f(0.5f, 0.0f, 1.0f); //Colour of the vertices
	//glVertex3f(2.0f, 1.0f, 0.0f); // Top
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(2.0f, -1.0f, 0.0f); // Bottom Left
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, -1.0f, 0.0f); // Bottom Right
	//glEnd();

	//glBegin(GL_TRIANGLES);
	//glColor3f(0.0f, 1.0f, 0.0f);   //Colour of the vertices
	//glVertex3f(-2.1f, 1.0f, 0.0f); // Top
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(-2.1f, -1.0f, 0.0f); // Bottom Left
	//glColor3f(0.5f, 0.0f, 1.0f);
	//glVertex3f(-0.1f, -1.0f, 0.0f); // Bottom Right
	//glEnd();



	int i = 0;

	while (i < 2){
	glBegin(GL_TRIANGLES);
	glColor3f(pos[i].r, pos[i].g, pos[i].b);
	glVertex3f(pos[i].x, pos[i].y, 0.0f);
	i++;
	glColor3f(pos[i].r, pos[i].g, pos[i].b);
	glVertex3f(pos[i].x, pos[i].y, 0.0f);
	i++;
	glColor3f(pos[i].r, pos[i].g, pos[i].b);
	glVertex3f(pos[i].x, pos[i].y, 0.0f);
	glEnd();
}
	
	

	//this isn't drawing the triangles... WHY!?
	//glBegin(GL_TRIANGLES);

	//for (int i = 0; i < 2; i++){
	//
	//	glColor3f(pos[i].r, pos[i].g, pos[i].b);
	//	glVertex3f(pos[i].x, pos[i].y, 0.0f);
	//	
	//}

	//glEnd();


	SDL_GL_SwapWindow(window);
}


//Function to initialise OpenGL
void initOpenGL()
{
	glcontext = SDL_GL_CreateContext(window);

	GLenum err = glewInit();

	if (GLEW_OK != err){
		/* Problem: glewInit failed, something is seriously wrong. */
		cout << "Error: " << glewGetErrorString(err) << endl;
	}

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

void initGeometry()
{
	//create buffer
	glGenBuffers(1, &triangleVBO);
	//make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//copy vertex data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

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
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

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
	glDeleteBuffers(1, &triangleVBO);
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
	initGeometry();
	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

	


	SDL_Event event;


	while (running){
		while (SDL_PollEvent(&event)){


			switch (event.type){

			case SDL_QUIT:
				running = false;
				break;
			case SDL_WINDOWEVENT_CLOSE:
				running = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){

				case SDLK_RIGHT:
					pos[0].x += 0.2f;
					pos[1].x += 0.2f;
					pos[2].x += 0.2f;
					break;
				case SDLK_LEFT:
					pos[0].x -= 0.2f;
					pos[1].x -= 0.2f;
					pos[2].x -= 0.2f;
					break;
				case SDLK_UP:
					pos[0].y += 0.2f;
					pos[1].y += 0.2f;
					pos[2].y += 0.2f;
					break;
				case SDLK_DOWN:
					pos[0].y -= 0.2f;
					pos[1].y -= 0.2f;
					pos[2].y -= 0.2f;
					break;
				default:
					break;
				}

			}
		}

		update();
		render();
	}


	CleanUp();

	return 0;


}

#pragma endregion