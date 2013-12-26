#ifndef JOUEUR
#define JOUEUR

#include <iostream>

class Joueur{
private:
	SDL_Surface * texture;
	int posx;
	int posy;
	std::string nick;
public:
	Joueur(int,int,std::string)
	int getPosX() const;
	int getPosY() const;
	void setX(int);
	void setY();
	void afficher();
	~Joueur();
};

#endif