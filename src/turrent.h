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
#include "SDL_ttf.h"
#endif

#include "turretbullet.h"
class Turrent{

public:
	//is the turrent active - still alive?
	bool active;

	//variable to hold the list of bullets
	vector<TurretBullet> bulletList;

	//string to hold the path to the turrent's texture
	string turrentPath;

	//turrent's texture to hold base and barrel images
	SDL_Texture *tBase;
	SDL_Texture *tBarrel;

	//turrent's SDL_Rect for the X,Y,W and H of base texture
	SDL_Rect baseRect;

	//turrt's SDL_Rect for the X,Y,W and H of barrel texture
	SDL_Rect barrelRect;

	//player's SDL_rect for the X, Y, W, and H of texture
	SDL_Rect posRect;

	//vars suing to get the angel between the turrent's position and the tank's position
	float x, y, turrentangle;

	//point that will be used dto rotate the turret - relative to the turrent barrel's RECT
	SDL_Point center;

	//floats for fireTime and and fireRate
	float fireTime = 0.0f;
	float fireRate = 1000.0f; //line second

	//audio soud effect - CHUNK
	Mix_Chunk *fire;

	//turrent's creation method using passed in values for renderer, player number, path to the texture
	//starting position X, starting position Y
	Turrent(SDL_Renderer * renderer, string filePath, string audioPath, float x, float y);

	//update the turrent using the passed in deltaTime
	void Update(float deltaTIme, SDL_Rect tankRect);

	//draw the turret main's passed in renderer
	void Draw(SDL_Renderer *renderer);

	//reset the turrent
	void Reset();

	//create a bullet
	void CreateBullet(SDL_Rect target);

	void TankMoveX(float tankSpeed, float deltaTime);

	void TankMoveY(float tankSpeed, float deltaTime);

	//float for the turrent's position to avoid precision loss
	float posB_X, posB_Y, posT_X, posT_Y;
};
