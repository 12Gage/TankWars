#include "enemyTank.h"

//tank creation method
EnemyTank::EnemyTank(SDL_Renderer *Renderer, string filepath, string audiopath, float x, float y)
{
	//active the turret
	active = false;

	//fire sound
	explode = Mix_LoadWAV((audiopath + "laser.wav").c_str());

	//create the turret base file path
	string basePath = filepath + "enemy.png";

	//load the image into the texture
	eTank = IMG_LoadTexture(Renderer, basePath.c_str());

	//set the SDL_Rect x and y for the base image
	eTankRect.x = x;
	eTankRect.y = y;

	//use SDL_WueryTexture to get the w and w of the base's texture
	int w,h;
	SDL_QueryTexture(eTank,NULL,NULL,&w,&h);
	eTankRect.w = w;
	eTankRect.h = h;

	posT_X = eTankRect.x;
	posT_Y = eTankRect.y;

	speed = 100;

	center.x = 32;
	center.y = 32;

	health = 10;
}

void EnemyTank::RemoveHealth()
{
	health -= 1;

	if(health <= 0){
		Reset();
	}
}

void EnemyTank::Reset()
{
	//reset the x position off the screen
	eTankRect.x = -1000;

	//update the pos_X for precision
	posT_X = eTankRect.x;

	health = 10;

	//deactivate the bullet
	active = false;
}

//tank moves the in x
void EnemyTank::eTankMoveX(float tankSpeed, float deltaTime)
{
	posT_X += (tankSpeed) *deltaTime;

	//update bullet position with code to account for precision loss
	eTankRect.x = (int)(posT_X + 0.5f);
}

//tank moves the in y
void EnemyTank::eTankMoveY(float tankSpeed, float deltaTime)
{
	posT_Y += (tankSpeed) *deltaTime;

	//update bullet position with code to account for precision loss
	eTankRect.y = (int)(posT_Y + 0.5f);

}

//turret draw method
void EnemyTank::Draw(SDL_Renderer *renderer)
{
	//draw the tank texture using the vars texture and posRect
	SDL_RenderCopyEx(renderer,eTank,NULL,&eTankRect,tankangle,&center,SDL_FLIP_NONE);
}

//tank update method
void EnemyTank::Update(float deltaTime, SDL_Rect tankRect)
{

	double distancex = (eTankRect.x - tankRect.x) * (eTankRect.x - tankRect.x);
	double distancey = (eTankRect.y - tankRect.y) * (eTankRect.y - tankRect.y);

	double calcdistance = sqrt(distancex + distancey);

	if(calcdistance <= 250){
		active = true;
	}else{
		active = false;
	}

	if(active){
		//get the angle between the tank and the turret
		x = (tankRect.x + (tankRect.w/2)) - (eTankRect.x + (eTankRect.w/2));
		y = (tankRect.y + (tankRect.h/2)) - (eTankRect.y + (eTankRect.h/2));
		tankangle = atan2(y,x) * 180/3.14;

		//give us radians
		float radians = (tankangle * 3.14)/180;


		//get need x and y values to move
		float move_x = speed * cos(radians);
		float move_y = speed * sin(radians);

		//update floats for precision loss
		posT_X += (move_x) * deltaTime;
		posT_Y += (move_y) * deltaTime;

		//update player position with code to account for precision loss
		eTankRect.x = (int)(posT_X + 0.5f);
		eTankRect.y = (int)(posT_Y + 0.5f);
	}

}
