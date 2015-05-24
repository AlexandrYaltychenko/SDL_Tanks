#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include <math.h>
#include "global.h"
#include "engine.h"
#include "objects.h"
void Object::SetSize(int w, int h){
	width=w;
	height=h;	
}
void Object::PutAt(int x, int y){
	xcor=x;
	ycor=y;
}
int Object::X(){
	return xcor;
}
int Object::Y(){
	return ycor;
}
int Object::Width(){
	return width;
}
int Object::Height(){
	return height;
}
void Object::MoveX(int x){
	PutAt(X()+x,Y());
}
void Object::MoveY(int y){
	PutAt(X(),Y()+y);
}
int Object::isSelected(){
	return selected;
}
void Object::setSelected(int a){
	selected=a;
}
int Object::isAt(int x, int y){
	if (x<xcor || y<ycor || x>xcor+width || y>ycor+height)
		return 0;
	else
		return 1;
}
int Object::isCollision(Object &obj){
	if (isAt(obj.X(),obj.Y()) || isAt(obj.X()+obj.Width(),obj.Y()+obj.Height()))
		return 1;
	else
		return 0;
}
int Object::inRect(int x1, int y1, int x2, int y2){
	if ((ycor < y1 || ycor+height > y2 || xcor+width < x1 || xcor > x2) && !isAt(x1,y1) && !isAt(x2,y2))
		return 0;
	else
		return 1;
}
void Tank::SetBodySprite(GLuint &a){
	sprites.body=&a;
}
void Tank::SetHeadSprite(GLuint &a){
	sprites.head=&a;
}
void Tank::SetHp(int h){
	hp=h;
}
void Tank::SetHeadAngle(int angle){
	sprites.hangle=angle;
}
void Tank::SetBodyAngle(int angle){
	sprites.angle=angle;
}
void Tank::SetAngle(int angle){
	sprites.hangle=sprites.angle=angle;
}
void Tank::RotateHead(int angle){
	sprites.hangle+=angle;
}
void Tank::RotateBody(int angle){
	sprites.angle+=angle;
}
void Tank::Rotate(int angle){
		sprites.hangle+=angle;
		sprites.angle+=angle;
}
void Tank::Draw(){
	if (isSelected())
	{
		Graphics.Draw(sprites.angle,X(),Y(),Width(),Height(),Graphics.textures[8]);
		if (motion.mx>=0)
			Graphics.Draw(angle++,motion.mx-128,motion.my-128,256,256,Graphics.textures[9]);
	}
	Graphics.Draw(sprites.angle,X(),Y(),Width(),Height(),*sprites.body);
	Graphics.Draw(sprites.hangle,X(),Y(),Width(),Height(),*sprites.head);
}
Tank::Tank(){
	hp=100;
	SetSize(200,100);
	PutAt(100,100);
	sprites.hangle=sprites.angle=0;
	setSelected(0);
	SetMoving(-1,-1);
}
Tank::Tank(GLuint &a, GLuint &b){
	sprites.body=&a;
	sprites.head=&b;
	SetSize(180,180);
	PutAt(100,100);
	setSelected(0);
	SetMoving(-1,-1);
}
void Tank::Move(int s){
	int x=s*cos(sprites.angle*2*3.14/360);
	int y=s*sin(sprites.angle*2*3.14/360);
	MoveY(x);
	MoveX(y);
	DrawWay();
	
}
void Tank::DrawWay(){
	Graphics.AddParticle(sprites.angle,X(),Y(),Width(),Height(),Graphics.textures[3]);
}

void Tank::SetMoving(int x, int y){
	motion.mx=x;
	motion.my=y;
}

void Tank::calcDirectSpeedTo(int x, int y){
	float k=(float)(y-Y())/(float)(x-X());
	sprites.angle=90-atan(k)*180/3.14;
	if (k<0)
	k=-k;
	motion.hspeed=5.*cos(atan(k));
	motion.vspeed=5.*sin(atan(k));
	//printf("startx=%d starty=%d x=%d y=%d hspeed=%d vspeed=%d %5.2f",X(),Y(),x,y,motion.hspeed,motion.vspeed,atan(k)*360/6.28);
}

void Tank::ReleaseMotion(){
	if (motion.mx<0 || (motion.mx==X() && motion.my==Y())) return;
	if (motion.mx>X())
	MoveX(motion.hspeed);
	else
	MoveX(-motion.hspeed);
	if (motion.my>Y())
	MoveY(motion.vspeed);
	else
	MoveY(-motion.vspeed);
	if (abs(X()-motion.mx)<motion.hspeed){
		PutAt(motion.mx,Y());
	}
	if (abs(Y()-motion.my)<motion.vspeed){
		PutAt(X(),motion.my);
	}
	DrawWay();
}
