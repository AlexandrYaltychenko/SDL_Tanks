#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include "global.h"
#include "engine.h"
#include "objects.h"
Application Game;
Engine Graphics;
int angle=0;
int main(){
	Graphics.Init();
	Graphics.LoadTextures();
	Graphics.Draw(0,0,1366,768,Graphics.textures[0]);
	units.push_back(Tank(Graphics.textures[1],Graphics.textures[2]));
	units[0].SetSize(180,180);
	units[0].Draw();
	Graphics.Render();
	while (1){
		while (SDL_PollEvent(&Graphics.signal)){
			Graphics.Input();
			if (Graphics.signal.type == QUIT) {
				Graphics.Close();
				Game.Close(0);
				}	
		}
			if (Graphics.Keys.left)
				units[0].Rotate(10);
			if (Graphics.Keys.right)
				units[0].Rotate(-10);
			if (Graphics.Keys.lctrl)
				units[0].RotateHead(10);
			if (Graphics.Keys.rctrl)
				units[0].RotateHead(-10);
			if (Graphics.Keys.up)
				units[0].Move(10);
			if (Graphics.Keys.down)
				units[0].Move(-10);
		Graphics.Draw(0,0,1366,768,Graphics.textures[0]);
		Graphics.DisplayParticles();
		units[0].Draw();
		Graphics.Selections();
		Graphics.MovingUnits();
		Graphics.Render();
		SDL_Delay(30);
	}
	Graphics.Close();
	Game.Close(0);
	return 0;
}

