#ifndef _BOMB
#define _BOMB

#include <SDL/SDL.h>


class Bomb{
private:
	int posx;
	int posy;
	int rayon;
	SDL_Surface * texture;
public:
	Bomb(int,int);
	Bomb(int,int,int);
	~Bomb();
};

#endif