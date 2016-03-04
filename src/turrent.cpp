#include "turrent.h"

//turrent creation method
Turrent::Turrent(SDL_Renderer *renderer, string filePath, string audioPath, float x, float y)
{
	//activate the turret
	active = true;

	//fire sound
	fire = Mix_LoadWAV((audioPath + "laser.wav").c_str());

	//create the turrent base file path
	string basePath = filePath + "turrentBase.png";

	//load the image into the texture
	tBase = IMG_LoadTexture(renderer, basePath.c_str());

	//create the turrent base file path
	string barrelPath = filePath + "turrentbarrel.png";

	//load the image into the texture
	tBarrel = IMG_LoadTexture(renderer, barrelPath.c_str());

	//set the sdl_Rect X and Y for the base image
	baseRect.x = x;
	baseRect.y = y;

	//use SDL_QueryTexture to get the W and H of the bas's texture
	int w, h;
	SDL_QueryTexture(tBase, NULL, NULL, &w, &h);
	baseRect.w = w;
	baseRect.h = h;

	//set the SDL_Rect X and Y for the barrel (used Photoshop to find this info)
	barrelRect.x = x + 20;
	barrelRect.y = y - 20;

	//use SDL_QueryTexture to get the W and H of the barrel's texture
	SDL_QueryTexture(tBarrel, NULL, NULL, &w, &h);
	barrelRect.w = w;
	barrelRect.h = h;

	//create the center point of the barrel texture for rotation (used photoshop to fin this info)
	center.x = 10;
	center.y = 10;

	//string to create the path to the player's bullert image
	string bulletPath = filePath + "tBullet.png";

	//create the turrent's bullet pool
	for(int i = 0; i < 10; i++)
	{
		//create the bullet and move offacreen, out of the game play area
		TurretBullet tmpBullet(renderer, bulletPath, 500, 500);

		//add to bulletList
		bulletList.push_back(tmpBullet);
	}

	//random null linit
	srand(time_t(NULL));

	//update the float values for movement
	posB_X = baseRect.x;
	posB_Y = baseRect.y;

	posT_X = barrelRect.x;
	posT_Y = barrelRect.y;

}

 //tank moves the turrent in X
void Turrent::TankMoveX(float tankSpeed, float deltaTime)
{
	posB_X += (tankSpeed) * deltaTime;
	posT_X += (tankSpeed) * deltaTime;

	//update bullet position with code to account for precision loss
	baseRect.x = (int)(posB_X + 0.5f);
	barrelRect.x = (int)(posT_X + 0.5f);
}

//tank moves the turrent in Y
void Turrent::TankMoveY(float tankSpeed, float deltaTime)
{
	posB_Y += (tankSpeed) * deltaTime;
	posT_Y += (tankSpeed) * deltaTime;

	//update bullet position with code to account for precision loss
	baseRect.y = (int)(posB_Y + 0.5f);
	barrelRect.y = (int)(posT_Y + 0.5f);
}

//turrent draw method
void Turrent::Draw(SDL_Renderer *renderer)
{

	 //draw the turret's bullets
	for(int i = 0; i < bulletList.size(); i++)
	{
		//check t see if the bullet is active
		if(bulletList[i].active){

			//draw bullet
			bulletList[i].Draw(renderer);
		}
	}

	//draw the base
	SDL_RenderCopy(renderer, tBase, NULL, &baseRect);

	//DRAW THE BARREL TEXTURE USING THE VARS TEXTURE AND POSRECT
	SDL_RenderCopyEx(renderer, tBarrel, NULL, &barrelRect, turrentangle, &center, SDL_FLIP_NONE);
}

//tank update method
void Turrent::Update(float deltaTime, SDL_Rect tankRect)
{
	//get the angle between the tank and the turrent
	x = (tankRect.x + (tankRect.w/2)) - (posRect.x + (baseRect.w/2));
	y = (tankRect.y + (tankRect.h/2)) - (posRect.y + (baseRect.h/2));
	turrentangle = atan2(y,x) * 180 / 3.14;

	if(SDL_GetTicks() > fireTime){

		if(baseRect.x > 0 && baseRect.x < 1024 && baseRect.y > 0 && baseRect.y < 768){
			CreateBullet(tankRect);
		}

		fireTime = SDL_GetTicks() + (rand() % 3+ 1) * 1000;
	}


	//update the turret's bullets
	for(int i =0; i < bulletList.size(); i ++)
	{
		//check to see if the bullet is active
		if(bulletList[i].active){

			//update bullet
			bulletList[i].Update(deltaTime);
		}
	}

}

//create a bullet
void Turrent::CreateBullet(SDL_Rect target)
{

	//see if there is a bullet active to fire
	for(int i = 0; i < bulletList.size(); i++)
	{
		//see if the bullet is noit active
		if(bulletList[i].active == false){

			bulletList[i].Start(target, baseRect);

			//play the over sound - plays fine through levls, must pause for quit
			Mix_PlayChannel(-1, fire, 0);

			//set bullet ot active
			bulletList[i].active = true;

			//use some math in the x poisiton to get the bullet close to
			//the center of the turret
			bulletList[i].posRect.x = ((baseRect.x + (baseRect.w/2)) - (bulletList[i].posRect.w/2));
			bulletList[i].posRect.y = ((baseRect.y + (baseRect.h/2)) - (bulletList[i].posRect.h/2));

			//set the x and y positions of the bullet's float positons
			bulletList[i].pos_X = bulletList[i].posRect.x;
			bulletList[i].pos_Y = bulletList[i].posRect.y;

			//once bullet is found, break out of loop
			break;
		}
	}

}
