#ifndef PLATEAU
#define PLATEAU

#include "Block.hpp"
#include <SDL/SDL.h>
#include <vector>


class Plateau{
private:
	SDL_Surface * background;
	std::vector<Block *> blocks;
public:
	
	~Plateau();
};

#endif