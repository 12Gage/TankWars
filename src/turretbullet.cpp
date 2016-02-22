#include "turretbullet.h"

//bullet creation method
TurretBullet::TurretBullet(SDL_Renderer *renderer, string filePath, float x, float y)
{
	//set the bullet initial stat
	active = false;

	//set bullet speed
	speed = 800.0;

	//creat the texture from the passed Renderer and created surface
	texture = IMG_LoadTexture(renderer, filePath.c_str());

	//set the width and height of the bullet's rectangle
	//by querying the texture itself
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	posRect.w = w;
	posRect.h = h;

	//set the x and y postions of the bullet rectangle
	//finishing aligning to the player center using the texture width
	posRect.x = x;
	posRect.y = y;
}

//reset the bullet method
void TurretBullet::Start(SDL_Rect playerPos, SDL_Rect turretPos) {

	player.x = playerPos.x;
	player.y = playerPos.y;

	turret.x = turretPos.x;
	turret.y = turretPos.y;

	distance = sqrt((player.x - turret.x * (player.x - turret.x) + (player.y - turret.y) * (player.y - turret.y)));
}

//reset the bullet method
void TurretBullet::Reset()
{
	//reset the x position off the screen
	posRect.x = -1000;

	//update tthe pos_x for precision
	pos_X = posRect.x;

	//deactivate the bullet
	active = false;
}

//bullet draw methd
void TurretBullet::Draw(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &posRect);
}

//bullet drawmethod
void TurretBullet::Update(float deltaTime) // float delta
{
	//get direction values to move with
	float vX = ((player.x - 32) - turret.x) / distance;
	float vY = ((player.y - 32) - turret.y) / distance;

	//increment the ullet position of vX and vY each frame
	pos_X += (vX * speed * deltaTime);
	pos_Y += (vY * speed * deltaTime);

	//update bullet position with code to account for precison loss
	posRect.x = (int)(pos_X + 0.5f);
	posRect.y = (int)(pos_Y + 0.5f);

	//check to see f the bullet is off the op of the screen
	//and deactivate and move off screen
	if ((posRect.y < (0 - posRect.h)) || (posRect.y > 768) || (posRect.x < (0 - posRect.w)) || (posRect.x > 1024)) {
		Reset();
	}
}