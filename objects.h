#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#ifndef H_OBJECTS
#define H_OBJECTS
class Object{
	private:
		int width;
		int height;
		int xcor;
		int ycor;
		int selected;
	public:
		void SetSize(int w, int h);
		int Width();
		int Height();
		int X();
		int Y();
		void MoveX(int x);
		void MoveY(int y);
		void PutAt(int x,int y);
		int isSelected();
		void setSelected(int a);
		int isAt(int x,int y);
		int inRect(int x1, int y1, int x2, int y2);
		int isCollision(Object &obj);
		Object(){
			width=height=xcor=ycor=selected=0;
		};
};
class Tank: public Object{
	private:
		struct View{
			GLuint *body;
			GLuint *head;
			int hwidth;
			int hheight;
			int angle;
			int hangle;
			View(){
				hangle=angle=0;				
			};
		};
		struct Moving{
			float mx;
			float my;
			float vspeed;
			float hspeed;
		};
		int hp;
	public:
		View sprites;
		Moving motion;
		void SetBodySprite(GLuint &a);
		void SetHeadSprite(GLuint &a);
		void SetHp(int h);
		void Draw();
		void SetHeadAngle(int angle);
		void SetBodyAngle(int angle);
		void SetAngle(int angle);
		void RotateHead(int angle);
		void RotateBody(int angle);
		void Rotate(int angle);
		void Move(int s);
		void DrawWay();
		void SetMoving(int x, int y);
		void ReleaseMotion();
		void calcDirectSpeedTo(int x, int y);
		Tank();
		Tank(GLuint &a, GLuint &b);
		
};
extern std::vector<Tank> units;
#endif
