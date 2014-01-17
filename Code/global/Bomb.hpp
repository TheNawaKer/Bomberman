#ifndef _BOMB
#define _BOMB

#include <SDL/SDL.h>
#include "FenetreSDL.hpp"

class Bomb{
private:
	int posx;
	int posy;
	int rayon;
	SDL_Surface * texture;
public:
	Bomb(int,int);
	Bomb(int,int,int);
	Bomb(Bomb &);
	int getPosX() const;
	int getPosY() const;
	~Bomb();
	void afficher(FenetreSDL * ecr);
};

#endif