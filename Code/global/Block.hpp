#ifndef _Block
#define _Block

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


class Block{
protected:
	int posx;
	int posy;
	int resistance;
	SDL_Surface * texture;
public:
	virtual void Briser()=0;
	virtual void Afficher()=0;
	int getPosX() const;
	int getPosY() const;
};


//penser a faire COPLIEN !!
#endif