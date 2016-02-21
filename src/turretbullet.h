#include <string>
#include <iostream>
#include "math.h"
using namespace std;

#if defined(__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif

class TurretBullet{

public:
	//boolean for the state of the bullet
	bool active;

	//bullet texture
	SDL_Texture *texture;

	//bullet rectangle for position (X,Y) and sizes (W,H)
	SDL_Rect posRect;

	//bullet speed
	float speed;

	//bullet float positions to prevent precision loss
	float pos_X, pos_Y;

	//poistion for the turrent and player
	SDL_Point turret, player;

	//distance between the z 
	float distance;

	//bullet creaton method, requirees the renderer, a path to the needed image, an Xposition, Y positon
	TurretBullet(SDL_Renderer *renderer, string filePath, float x, float y);


	//bullet upate - requires deltaTime be passed
	void Upate(float deltaTime);

	//bulllet draw - requires renderer be passed
	void Draw(SDL_Renderer *renderer);

	//buller reset;
	void Reset();

	//bullet start
	void Start(SDL_Rect playerPos, SDL_Rect turretPos);
	
};
