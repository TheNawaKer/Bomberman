#include "Joueur.hpp"
#include <iostream>
using namespace std;

Joueur::Joueur(int x,int y,string pseudo):posx(x),posy(y),nick(pseudo){}

int Joueur::getPosX() const{
	return posx;
}

int Joueur::getPosY() const{
	return posy;
}

void Joueur::setX(int x){
	posx=x;
}

void Joueur::setY(int y){
	posy=y;
}

Joueur::~Joueur(){
	if(texture)
		SDL_FreeSurface(texture);
}

void Joueur::Afficher(FenetreSDL * ecr){

}