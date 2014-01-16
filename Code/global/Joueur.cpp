#include "Joueur.hpp"
#include <iostream>
using namespace std;

Joueur::Joueur(int x,int y,string pseudo):posx(x),posy(y),nick(pseudo){
	texture=NULL;
}

Joueur::Joueur(int x,int y,string pseudo,string img):posx(x),posy(y),nick(pseudo){
	img+=".png";
	cout<<img<<endl;
	texture=IMG_Load(img.c_str());
}

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

string Joueur::getNick() const{
	return nick;
}

Joueur::~Joueur(){
	if(texture)
		SDL_FreeSurface(texture);
}

void Joueur::afficher(FenetreSDL * ecr){
	if(texture!=NULL)
		ecr->blit(40+posx*40,60+posy*40,texture);
}