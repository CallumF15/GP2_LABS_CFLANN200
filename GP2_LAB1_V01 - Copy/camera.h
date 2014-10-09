#ifndef camera_h
#define camera_h

//Following LazyFoo's tutorial
//http://lazyfoo.net/SDL_tutorials/lesson21/index.php

class camera{

private:
	//The X and Y offsets of the dot
	int x, y;

	//The velocity of the dot
	int xVel, yVel;

public:
	//Initializes the variables
	camera();

	//Takes key presses and adjusts the dot's velocity
	void handle_input();

	//Moves the dot
	void move();

	//Shows the dot on the screen
	void show();

	//Sets the camera over the dot
	void set_camera();
};

#endif