#ifndef JOUEUR
#define JOUEUR

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include "FenetreSDL.hpp"

class Joueur{
private:
	SDL_Surface * texture;
	int posx;
	int posy;
	std::string nick;
public:
	Joueur(int,int,std::string,std::string);
	Joueur(int,int,std::string);
	int getPosX() const;
	int getPosY() const;
	std::string getNick() const;
	void setX(int);
	void setY(int);
	void afficher(FenetreSDL * ecr);
	~Joueur();
};

#endif