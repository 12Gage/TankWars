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


class Jewel{

public:

	//is the jwel active
	bool active;

	//jewel's texture to hold jewel images
	SDL_Texture *jewel;

	//jewel's SDL_rect for the x, y, w, and h of base texture
	SDL_Rect jewelRect;

	//float for the jewel's poistion to avoid precision loss
	float posJ_X, posJ_Y;

	//jewel's creation method
	Jewel(SDL_Renderer*renderer, string filePath, int color, float x, float y);

	//draw the jewel using main's passed in renderer
	void Draw(SDL_Renderer*renderer);

	//update the jewel using the passed in deltaTIme
	void Update(float deltaTIme);

	void TankMoveX(float tankSpeed, float deltaTime);

	void TankMoveY(float tankSpeed, float deltaTime);

};
