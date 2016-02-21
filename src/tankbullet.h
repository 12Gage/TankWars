#include <string>
#include <iostream>
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

class TankBullet{

public:

	//is the player active - still alive?
	bool active;

	//player's teutre to hold img
	SDL_Texture *texture;

	//player's SDL_rect for the X, Y, W, and H of texture
	SDL_Rect posRect;

	//floats to hold the joystick axis(-1 or 0 or 1)
	float xDir, yDir;

	//float for player speed
	float speed;

	//bullet float positionsw to prevent precision loss
	float pos_X, pos_Y;

	//bullet creation method. requires the renderer, a path to the needed image, an X position, a Y position
	TankBullet(SDL_Renderer *renderer, string filePath, float x, float y, int dirX, int dirY);

	//bullet update - requires  deltaTime be passed
	void Update(float deltaTime);

	//bullet draw - requires renderer be passed
	void Draw(SDL_Renderer * renderer);

	//bullet reset
	void Reset();
};
