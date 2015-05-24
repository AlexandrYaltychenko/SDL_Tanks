#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include "engine.h"
#include <vector>
#include "objects.h"
#include <stdio.h>
int mx,my;
std::vector<Tank> units;
void Engine::Init(){
	//Инициализация TTF матрицы
	TTF_Init();
	//Подключение двойной буферизации
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//Создание окна
	window = SDL_CreateWindow("Stars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//Активация полноэкранного режима
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	context = SDL_GL_CreateContext(window);
	//Инициализация GL-матрицы
	glOrtho(0.0f, 1366.0f, 768.0f, 0.0f, -1.0f, 1.0f);
}

void Engine::Close(){
	//Уничтожение окна
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	//Закрытие SDL
	SDL_Quit();
	//Деинициализация TTF матрицы
	TTF_Quit();
}

void Engine::Draw(int x, int y, int width, int height, GLuint img){
	/*Вывод текстуры по координатам*/
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, img);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);
	glVertex2f(x, y);
	glTexCoord2f(1, 0);
	glVertex2f(x + width, y);
	glTexCoord2f(1, 1);
	glVertex2f(x + width, y + height);
	glTexCoord2f(0, 1);
	glVertex2f(x, y + height);
	glEnd();
	glPopMatrix();
}

void Engine::Draw(int angle,int x,int y, int width, int height,  GLuint img){
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5,0.5,0.0);
	glRotatef(angle,0.0,0.0,0.5);
	glTranslatef(-0.5,-0.5,0.0);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, img);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);
	glVertex2i(x, y);
	glTexCoord2i(1, 0);
	glVertex2i(x + width, y);
	glTexCoord2i(1, 1);
	glVertex2i(x + width, y + height);
	glTexCoord2i(0, 1);
	glVertex2i(x, y + height);
	glEnd();
	glPopMatrix();
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
}
void Engine::Rectangle(int x1,int y1, int x2,int y2){
	Draw(x1,y1,x2-x1,y2-y1,textures[7]);
}
GLuint Engine::LoadTex(std::string filename){
	/*Загрузка текстуры из filename*/
	GLuint r;
	SDL_Surface* Surface = IMG_Load(filename.c_str());
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glGenTextures(1, &r);
	glBindTexture(GL_TEXTURE_2D, r);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	int Mode = GL_RGB;
	if (Surface->format->BytesPerPixel == 4) {
		Mode = GL_RGBA;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, Surface->format->BytesPerPixel, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(Surface);
	return r;
}

void Engine::LoadTextures(){
	textures.push_back(LoadTex(".//textures//backgrounds//sand.jpg"));
	textures.push_back(LoadTex(".//textures//tanks//1.png"));
	textures.push_back(LoadTex(".//textures//tanks//1_2.png"));
	textures.push_back(LoadTex(".//textures//effects//1.png"));
	textures.push_back(LoadTex(".//textures//effects//2.png"));
	textures.push_back(LoadTex(".//textures//effects//3.png"));
	textures.push_back(LoadTex(".//textures//effects//4.png"));
	textures.push_back(LoadTex(".//textures//effects//5.png"));
	textures.push_back(LoadTex(".//textures//tanks//1_3.png"));
	textures.push_back(LoadTex(".//textures//effects//6.png"));
}

void Engine::Render(){
	SDL_GL_SwapWindow(window);
}
void Engine::MakeSelections(){
		//printf("Jorik! %d \n",units.size());
	//	exit(units.size());
	if (units.size()<1 || units.size()>1000)
	return;
	for(auto i = units.begin(); i != units.end();)
		{
			printf("Jorik! %d \n",units.size());
		if (i->inRect(last.mcx,last.mcy,mx,my) || i->inRect(mx,my,last.mcx,last.mcy))
			{
				i->setSelected(1);
			}
		else
			i->setSelected(0);
		++i;
		}
}
void Engine::Input(){
	SDL_GetMouseState(&mx, &my);
		if (Graphics.signal.type == KEYDOWN) {
				switch (Graphics.signal.key.keysym.sym) {
					case SDLK_LEFT:
						Keys.left=1;
						break;
					case SDLK_RIGHT:
						Keys.right=1;
						break;
					case SDLK_LCTRL:
						Keys.lctrl=1;
						break;
					case SDLK_RCTRL:
						Keys.rctrl=1;
						break;
					case SDLK_UP:
						Keys.up=1;
						break;
					case SDLK_DOWN:
						Keys.down=1;
						break;
					}
				}
		if (Graphics.signal.type == KEYUP) {
				switch (Graphics.signal.key.keysym.sym) {
					case SDLK_LEFT:
						Keys.left=0;
						break;
					case SDLK_RIGHT:
						Keys.right=0;
						break;
					case SDLK_LCTRL:
						Keys.lctrl=0;
						break;
					case SDLK_RCTRL:
						Keys.rctrl=0;
						break;
					case SDLK_UP:
						Keys.up=0;
						break;
					case SDLK_DOWN:
						Keys.down=0;
						break;
					}
				}
		if (Graphics.signal.type == SDL_MOUSEBUTTONUP) {
			if (Graphics.signal.button.button==SDL_BUTTON_LEFT)
			{
				MakeSelections();
				Keys.lmouse=0;
			}
			if (Graphics.signal.button.button==SDL_BUTTON_RIGHT){
				Keys.rmouse=0;
			}
		}
		if (Graphics.signal.type == SDL_MOUSEBUTTONDOWN) {
			if (Graphics.signal.button.button==SDL_BUTTON_LEFT)
			{
				Keys.lmouse=1;
				last.mcx=mx;
				last.mcy=my;
								/*if (units[0].isSelected())
					{
						exit(0);
						units[0].SetMoving(mx,my);
					}*/
			}
			if (Graphics.signal.button.button==SDL_BUTTON_RIGHT)
			{
				Keys.rmouse=1;
					if (units[0].isSelected())
					{
						units[0].SetMoving(mx,my);
						units[0].calcDirectSpeedTo(mx,my);
					}
			}
		}
}

void Engine::AddParticle(int a,int x, int y, int w, int h, GLuint &t){
	particles.push_back(Particle(a,x,y,w,h,t));
}

void Engine::DisplayParticles(){
	for(auto i = particles.begin(); i != particles.end();)
		{
		Draw(i->angle,i->xcor,i->ycor,i->height,i->width,*i->tex);
		i->ms--;
		if (i->ms<15)
			i->tex=&textures[6];
		else
		if (i->ms<25)
			i->tex=&textures[5];
		else
		if (i->ms<40)
			i->tex=&textures[4];			
		if (i->ms==0)
			particles.erase(i);
		else
		++i;
		}
}

void Engine::Selections(){
	if (Keys.lmouse){
		Rectangle(last.mcx,last.mcy,mx,my);
	}
}

void Engine::MovingUnits(){
	if (units[0].motion.mx<0 || (units[0].motion.mx==units[0].X() && units[0].motion.my==units[0].Y())) return;
	units[0].ReleaseMotion();
}
