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

//needed includes
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#include "tankbullet.h"

class Tank{

public:
	//is the player active - still alive?
	bool active;

	//variable to hold the list of bullets
	vector<TankBullet> bulletList;

	//string to hold the path to the player's texture
	string playerPath;

	//integer for the player's number
	int playerNum;

	//player's teutre to hold img
	SDL_Texture *texture;

	//player's SDL_rect for the X, Y, W, and H of texture
	SDL_Rect posRect;

	//floats to hold the joystick axis(-1 or 0 or 1)
	float xDir, xDirOld;
	float yDir, yDirOld;

	//float for player speed
	float speed;

	//float for the players position to avoid precision loss
	float pos_X, pos_Y;

	//vars used to get the angel between the tank's position and the joystick position
	float x, y, tankangle;

	//point that will be used to rotate the turrent - relative to the turrent barrel's RECT
	SDL_Point center;

	//keep the last angle so the player can fire in the corrrect direction
	float oldAngle;

	//audio sound effeect - CHUNK
	Mix_Chunk *fire;

	//player's creation method using passed in valuues for renderer, player number, path to the texture
	//starting position X, starting position Y
	Tank (SDL_Renderer *renderer, int pNum, string filePath, string sudioPath, float x, float y);

	//method to allow the player the move via joystock axis
	void OnControllerAxis(const SDL_ControllerAxisEvent event);

	//method to allow the player interact woth joystick buttons
	void OnControllerButton(const SDL_ControllerButtonEvent event);

	//update the player using the passed in deltaTime
	void Update(float deltaTime);

	//draw thjs player main's passed in renderer
	void Draw(SDL_Renderer * renderer);

	//reset the player
	void Reset();

private:

	void CreateBUllet();

};
