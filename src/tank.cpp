#include "tank.h"

//analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

//tank creation
Tank::Tank(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y)
{

	//activate the player
	active = true;

	//set the player number 0 or 1
	playerNum = pNum;

	//set float for player speed
	speed = 200.0f;

	//tank firing sound
	fire = Mix_LoadWAV((audioPath + "fire.wav").c_str());

	//see if this is player 1, or player 2, and create the correct file path
	if(playerNum == 0){
		//tank path to image
		playerPath = filePath + "tank1.png";
	}else{
		//create the blue tank texture
		playerPath = filePath + "blueTank.png";
	}

	//load the surface into the texture
	texture = IMG_LoadTexture(renderer, playerPath.c_str());

	//set the SDL_Rect X and Y for the player
	posRect.x = x;
	posRect.y = y;
	posRect.w = 64;
	posRect.h = 64;

	//set the movement floats to the players original X and Y
	pos_X = x;
	pos_Y = y;

	//set the xDir and yDir for the joysticks
	xDir = 0;
	yDir = 0;

	//set initial values so the tank can shoot
	xDirOld = 1;
	yDirOld = 0;

	//center of the image rectangle
	center.x = posRect.w/2;
	center.y = posRect.h/2;

	//string to create the path to the player's bullet image
	string bulletPath;

	//see if this is player 1 or player 2, and create the correct file path
	if(playerNum == 0){
		//create the bullet 1 texture
		bulletPath = filePath + "redBullet.png";
	}else{
		//create the bullet 2 texture
		bulletPath = filePath + "blueBullet.png";
	}

	//create the player's bullet pool
	for(int i = 0; i < 10; i++)
	{
		//create the bullet and move offscreen, out of the game play area
		TankBullet tmpBullet(renderer,bulletPath,-1000,-1000,0,0);

		//add to bulletlist
		bulletList.push_back(tmpBullet);
	}

}


void Tank::Update(float deltaTime)
{
	//check for gampad input
	if(xDir != 0 || yDir != 0){
		//get the angle between the tank and the turret
		x = posRect.x - xDir;
		y = posRect.y - yDir;
		tankangle = atan2(yDir,xDir) * 180/3.14;
		//set this as the old angfle and dir some the player/tank can shoot when stopped
		oldAngle = tankangle;
		xDirOld = xDir;
		yDirOld = yDir;
	}else {
		tankangle = oldAngle;
	}
	//adjust position floats based on speed, direction of joystick axis and deltaTime
	pos_X += (speed* xDir) * deltaTime;
	pos_Y += (speed* yDir) * deltaTime;

	//update player position with code to account for precision loss
	posRect.x = (int)(pos_X + 0.5f);
	posRect.y = (int)(pos_Y + 0.5f);

	//check if the tank is off screen and set it back
	if(posRect.x < 0){
		posRect.x = 0;
		pos_X = posRect.x;
	}

	if(posRect.x > 1024 - posRect.w){
		posRect.x = 1024 - posRect.w;
		pos_X = posRect.x;
	}

	if(posRect.y < 0){
		posRect.y = 0;
		pos_Y = posRect.y;
	}

	if(posRect.y > 768 - posRect.h){
		posRect.y = 768 - posRect.h;
		pos_Y = posRect.y;
	}

	//update the tank's bullets
	  for(int i = 0; i< bulletList.size(); i++)
	  {
		  //check to see if the bullet is active
		  if(bulletList[i].active){

			  //update bullet
			  bulletList[i].Update(deltaTime);
		  }
	  }
}


void Tank::Draw(SDL_Renderer *renderer)
{
	//draw the player's bullets
	for(int i = 0; i < bulletList.size(); i++)
	{
		//check to see if the bullet is active
		if(bulletList[i].active){

			//draw bullet
			bulletList[i].Draw(renderer);
		}
	}

	//draw the player texture using the cars texture and posRect
	SDL_RenderCopyEx(renderer, texture, nullptr, &posRect, tankangle, &center, SDL_FLIP_NONE);

}

//player joystick button method
void Tank::OnControllerButton(const SDL_ControllerButtonEvent event)
{
	//if the player's number is 0 and the joystick button is from joystick 0
	if(event.which == 0 && playerNum == 0)
	{
		//if A button
		if(event.button == 0)
		{
			//create a bullet
			CreateBullet();

		}

	}

	//if the player's number is 1 and the joystick button is from joystick 1
	if(event.which == 1 && playerNum == 1)
	{
		//if A button
		if(event.button == 0)
		{

			//create a bullet
			CreateBullet();

		}
	}
}

void Tank::OnControllerAxis(const SDL_ControllerAxisEvent event)
{
//if the player's number is 0  and the joystick axis is from joystick 0
	if(event.which == 0 && playerNum == 0)
	{
		//X axis
		if(event.axis == 0)
		{
			if(event.value < - JOYSTICK_DEAD_ZONE)
			{
				xDir = -1.0f;//left
			}
			else if(event.value > JOYSTICK_DEAD_ZONE)
			{
				xDir = 1.0f; //right
			}
			else
			{
				xDir = 0.0f;//none
			}
		}

		//Y axis
		if(event.axis == 1)
		{
			if(event.value < - JOYSTICK_DEAD_ZONE)
			{
				yDir = -1.0f;//left
			}
			else if(event.value > JOYSTICK_DEAD_ZONE)
			{
				yDir = 1.0f; //right
			}
			else
			{
				yDir = 0.0f;//none
			}
		}
	}

	if(event.which == 1 && playerNum == 1)
	{
		//X axis
		if(event.axis == 0)
		{
			if(event.value < - JOYSTICK_DEAD_ZONE)
			{
				xDir = -1.0f;//left
			}
			else if(event.value > JOYSTICK_DEAD_ZONE)
			{
				xDir = 1.0f; //right
			}
			else
			{
				xDir = 0.0f;//none
			}
		}

		//Y axis
		if(event.axis == 1)
		{
			if(event.value < - JOYSTICK_DEAD_ZONE)
			{
				yDir = -1.0f;//left
			}
			else if(event.value > JOYSTICK_DEAD_ZONE)
			{
				yDir = 1.0f; //right
			}
			else
			{
				yDir = 0.0f;//none
			}
		}
	}
}

//create a bullet
void Tank::CreateBullet(){

	//see if there is a bullet active to fire
	for(int i = 0; i < bulletList.size(); i ++)
	{
		//see if the bullet is not active
		if(bulletList[i].active == false){

		//play the over sound - plays fine through levels, must pause for quit
		Mix_PlayChannel(-1 ,fire, 0);

		//set bullet to active
		bulletList[i].active = true;

		//use some math in the x position to get the bullet close to
		//the corner of the player using player width
		bulletList[i].posRect.x = (posRect.x + (posRect.w/2));
		bulletList[i].posRect.y = (posRect.y + (posRect.h/2));

		//fininshing aligning to the player center using the texture width
		bulletList[i].posRect.x = bulletList[i].posRect.x - (bulletList[i].posRect.w/2);
		bulletList[i].posRect.y = bulletList[i].posRect.y - (bulletList[i].posRect.h/2);

		//set the x and y positions of the bullet's float positions
		bulletList[i].pos_X = bulletList[i].posRect.x;
		bulletList[i].pos_Y = bulletList[i].posRect.y;

		//if the tank is moving fire in the direction
		if(xDir != 0 || yDir != 0){
			//set the x and y positions fo the bullet's float positions
			bulletList[i].xDir = xDir;
			bulletList[i].yDir = yDir;
		}else{
			//if the tank is not moving, fire in the direction currently facing
			//set the x and y positions of the bullet's float positions
			bulletList[i].xDir = xDirOld;
			bulletList[i].yDir = yDirOld;
			}

		//once bullet is found, break out of loop
		break;

		}
	}
}
