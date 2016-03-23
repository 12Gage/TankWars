#include "jewel.h"

//jewel creation method
Jewel::Jewel(SDL_Renderer *renderer, string filePath, int color, float x, float y)
{
	active = true;

	if(color == 0){

		//create the jewel base file path
		string basePath = filePath + "purple.png";

		//load the image into the texture
		jewel = IMG_LoadTexture(renderer, basePath.c_str());

	}else if(color == 1){

		//create the jewel base file path
		string basePath = filePath + "red.png";

		//load the image into the texture
		jewel = IMG_LoadTexture(renderer, basePath.c_str());

	}else if(color == 2){

		//create the jewel base file path
		string basePath = filePath + "blue.png";

		//load the image into the texture
		jewel = IMG_LoadTexture(renderer, basePath.c_str());

	}else if(color == 3){

			//create the jewel base file path
			string basePath = filePath + "folderPickup.png";

			//load the image into the texture
			jewel = IMG_LoadTexture(renderer, basePath.c_str());

		}

	//set the SDL_Rect x and y for the base iamge
	jewelRect.x = x;
	jewelRect.y = y;

	//use SDL_QueryTexture to get the w and h of the base's texture
	int w, h;
	SDL_QueryTexture(jewel, NULL, NULL, &w, &h);
	jewelRect.w = w;
	jewelRect.h =h;

	posJ_X = jewelRect.x;
	posJ_Y = jewelRect.y;

}

//jewel Draw method
void Jewel::Draw(SDL_Renderer * renderer)
{
	//draw the base
	SDL_RenderCopy(renderer, jewel, NULL, &jewelRect);

}

//tank moves the jewel
void Jewel::TankMoveX(float tankSpeed, float deltaTime)
{
	posJ_X += (tankSpeed * deltaTime);

	//update jewel position with code to account for precision loss
	jewelRect.x = (int)(posJ_X + 0.5f);

}

//tank moves the jewel
void Jewel::TankMoveY(float tankSpeed, float deltaTime)
{
	posJ_Y += (tankSpeed * deltaTime);

	//update jewel position with code to account for precision loss
	jewelRect.y = (int)(posJ_Y + 0.5f);

}
