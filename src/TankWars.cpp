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
#include <direct.h>
#define getcw _getcw

string images_dir = currentWorkingDirectory + "/src/";
string audio_dir = currentWorkingDirectory + "/src/";

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <unistd.h>

string images_dir = currentWorkingDirectory + "/src/";
string audio_dir = currentWorkingDirectory + "/src/";

#endif

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdint.h>

#include "tank.h"

using namespace std;

#if defined(__APPLE__)
//string car to hold the current working directory on _APPLE_
string currentWorkingDirectory(getcwd(NULL, 0));

//create a string to link the images folder on _APPLE_
string images_dir = currentWorkingDirectory + "/src/";

//week 5
//create a string to link the audio folder on _APPLE_
string audio_dir = currentWorkingDirectory + "/src/";
#endif

//deltaTime var intializartion - for frame rate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

//main start
int main(){

	//create the SDL Window - start
	//start SDL2
	SDL_Init(SDL_INIT_EVERYTHING);


//create a SDL Window refernece - pointer
	SDL_Window* window = nullptr;

	//create a SDL RenderTarget - pointer
	SDL_Renderer *renderer= nullptr;

	//create a SDL Window in the midddle of the ascreen
	window = SDL_CreateWindow("Tank Wars!",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1024,768,
			SDL_WINDOW_SHOWN);

	//create an SDL RenderTarget
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//create the SDL Window - end

	//variable createtion - start
	//main loop flag
	bool quit = false;

	//event handler
	SDL_Event e;
	//variable creation - end

	//turn on game controller events
	SDL_GameControllerEventState(SDL_ENABLE);

	//set up a game controller variable for player 1
	SDL_GameController* gGameController0 = NULL;

	//open game controller for player 1
	gGameController0 = SDL_GameControllerOpen(0);

	//open adui channel
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//load a music file
	Mix_Music *bgm = Mix_LoadMUS((audio_dir + "background.mp3").c_str());

	//if the music file is not playing - play it
	if(!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);

	//create player - start
	Tank tank1 = Tank(renderer, 0, images_dir.c_str(), audio_dir.c_str(), 50.0,50.0);

	//main game loop start

	while(!quit)
	{
		//create deltaTime - for frame rate independence
		thisTime = SDL_GetTicks();
		deltaTime = (float)(thisTime - lastTime)/1000;
		lastTime = thisTime;

		//handle events on queue - keypresses and such stardt
		while(SDL_PollEvent(&e) != 0)
		{
			//user method quit
			if(e.type == SDL_QUIT)
			{
				quit = true;

			}

			switch(e.type){

			case SDL_CONTROLLERBUTTONDOWN:

				if(e.cdevice.which == 0){

					if(e.cbutton.button == SDL_CONTROLLER_BUTTON_A){

						break;
					}

				}

				break;

			case SDL_CONTROLLERAXISMOTION:
				tank1.OnControllerAxis(e.caxis);
			break;

			}




		}//POLL EVENT

		//upate player 1 tank
		tank1.Update(deltaTime);

		//draw section
		//clear the SDL RendererTarget
		SDL_RenderClear(renderer);

		tank1.Draw(renderer);

		SDL_RenderPresent(renderer);

	}
	//close and destroy the window
	SDL_DestroyWindow(window);

	//clean up
	SDL_Quit();

	return 0;
}
