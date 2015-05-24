#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include "global.h"
Application::Application(){
	timeout=clock();
}

int Application::Timeout(){
	return timeout;
}

void Application::Close(int arg){
	exit(arg);
}



