#ifndef _Block
#define _Block

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "FenetreSDL.hpp"

class Block{
protected:
	int posx;
	int posy;
	int resistance;
	SDL_Surface * texture;
public:
	Block(int x,int y,int resistance);
	Block(Block & block);
	virtual void Briser()=0;
	virtual void afficher(FenetreSDL * ecr);
	int getPosX() const;
	int getPosY() const;
};


//penser a faire COPLIEN !!
#endif