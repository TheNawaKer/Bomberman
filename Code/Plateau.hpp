#ifndef PLATEAU
#define PLATEAU

#include "Block.hpp"
#include <SDL/SDL.h>


class Plateau{
private:
	SDL_Surface * background;
	Block * tab;
public:
	
	~Plateau();
};

#endif