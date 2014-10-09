#include "camera.h"


#pragma region Variables

	int x, y;
	int xVel, yVel;

	//The X and Y offsets of the dot
	int mPosX, mPosY;
	//The velocity of the dot
	int mVelX, mVelY;

	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 10;

	//The dimensions of the level
	const int LEVEL_WIDTH = 1280;
	const int LEVEL_HEIGHT = 960;

	//The dot that will be moving around on the screen
	camera dot;

	//The camera area
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


#pragma endregion 

	


	void move()
	{
		//Move the dot left or right
		mPosX += mVelX;

		//If the dot went too far to the left or right
		if ((mPosX < 0) || (mPosX + DOT_WIDTH > LEVEL_WIDTH))
		{
			//Move back
			mPosX -= mVelX;
		}

		//Move the dot up or down
		mPosY += mVelY;

		//If the dot went too far up or down
		if ((mPosY < 0) || (mPosY + DOT_HEIGHT > LEVEL_HEIGHT))
		{
			//Move back
			mPosY -= mVelY;
		}
	}

	void set_camera()
	{
		//Center the camera over the dot
		camera.x = (x + DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
		camera.y = (y + DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

		//Keep the camera in bounds.
		if (camera.x < 0)
		{
			camera.x = 0;
		}
		if (camera.y < 0)
		{
			camera.y = 0;
		}
		if (camera.x > LEVEL_WIDTH - camera.w)
		{
			camera.x = LEVEL_WIDTH - camera.w;
		}
		if (camera.y > LEVEL_HEIGHT - camera.h)
		{
			camera.y = LEVEL_HEIGHT - camera.h;
		}
	}

