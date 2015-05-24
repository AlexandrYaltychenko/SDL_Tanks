#include <vector>
#ifndef H_ENGINE
#define H_ENGINE
#define QUIT SDL_QUIT
#define KEYDOWN SDL_KEYDOWN
#define KEYUP SDL_KEYUP
class Engine{
	private:
		int fps;
		SDL_GLContext context;
		SDL_Window* window;
		GLuint LoadTex(std::string filename);
	public:
	struct BKeys{
		int left=0;
		int right=0;
		int lctrl=0;
		int rctrl=0;
		int up=0;
		int down=0;
		int lmouse=0;
		int rmouse=0;
	};
	struct Last{
		int mcx,mcy;
	};
	struct Particle{
		int ms;
		int xcor;
		int ycor;
		int width;
		int height;
		GLuint * tex=NULL;
		int angle;
		Particle(int a,int x,int y,int w,int h,GLuint &t){
			angle=a;
			xcor=x;
			ycor=y;
			width=w;
			height=h;
			tex=&t;
			ms=50;
		};
	};
		std::vector<Particle> particles;
		BKeys Keys;
		Last last;
		std::vector<GLuint> textures;
		SDL_Event signal;
		void Init();
		void LoadTextures();
		void Close();
		void DisplayParticles();
		void DisplayUnits();
		void Render();
		void MovingUnits();
		void Draw(int x, int y, int width, int height, GLuint img);
		void Draw(int angle, int x, int y, int width, int height, GLuint img);
		void Rectangle(int x1,int y1,int x2, int y2);
		void MakeSelections();
		void Input();
		void AddParticle(int a,int x, int y, int w, int h, GLuint &t);
		void Selections();
};

GLuint LoadText(std::string filename);

void drawpartimage(int x, int y, float startx, float starty, float endx, float endy, int width, int height, GLuint img);

void angledraw(int x,int y, int width, int height, int angle, GLuint img);

void RenderText(const TTF_Font *Font, const GLubyte& R, const GLubyte& G, const GLubyte& B,
	const double& X, const double& Y, const std::string& Text);

extern Engine Graphics;

#endif
