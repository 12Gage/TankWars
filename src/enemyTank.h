#include <string>
#include <iostream>

using namespace std;
#include <vector>

#if defined(__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#endif

class EnemyTank{

public:

	//is the tank active - still alive
	bool active;

	//string to hold the path to the tank's texture
	string eTankPath;

	//tank's texture to hold base and barrel images
	SDL_Texture *eTank;

	//tank's SDL_Rect for the X,Y,W ,and H of base texture
	SDL_Rect eTankRect;

	//vars used to get the angle between the tank's position and the player's position
	float x,y,tankangle;

	//audio sound effect - chunk
	Mix_Chunk *explode;

	//tank speed
	float speed;

	//tank health
	int health;

	//point that will be used to rotate the tank
	SDL_Point center;

	//enemy tank's creation method using passed in values for renderer, player number, path to the texture
	//starting positon X, STARTING POSITION Y
	EnemyTank(SDL_Renderer *renderer, string filepath, string audiopath, float x, float y);

	//update the enemytank using the passed in deltaTime
	void Update(float deltaTime, SDL_Rect etankRect);

	//draw the enemytank main's passed in renderer
	void Draw(SDL_Renderer *renderer);

	//reset the turret
	void Reset();

	//remove helath
	void RemoveHealth();

	void eTankMoveX(float tankSpeed, float deltaTime);

	void eTankMoveY(float tankSpeed, float deltaTime);

	//float for the turren's position to avoid preceision loss
	float posT_X, posT_Y;


};
