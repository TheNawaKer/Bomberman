#ifndef PLATEAU
#define PLATEAU

#include "Block.hpp"
#include "Bomb.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include "FenetreSDL.hpp"


class Plateau{
private:
	SDL_Surface * background;
	std::vector<Block *> blocks;
	std::vector<Bomb> bombs;
	//Joueur * joueur[4];
public:
	Plateau();
	void DetruireBlock(int x,int y);
	void ajouterBombe(int x,int y);
	void enleverBomb(int x,int y);
	~Plateau();
	void afficher(FenetreSDL * ecr);
};

#endif