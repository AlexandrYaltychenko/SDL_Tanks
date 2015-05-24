#ifndef H_GLOBAL
#define H_GLOBAL
class Application{
	private:
		long int timeout;
		int state;
	public:
		Application();
		int Timeout();
		void Close(int arg);
};
extern Application Game;
extern int mx,my;
extern int angle;
#endif
