#include "Bomb.hpp"



Bomb::Bomb(int x, int y):posx(x),posy(y),rayon(1){
	texture=IMG_Load("../ressources/game/bomb.png");
}


Bomb::Bomb(int x, int y,int r):posx(x),posy(y),rayon(r){
	texture=IMG_Load("../ressources/game/bomb.png");
}

Bomb::Bomb(Bomb & b):posx(b.posx),posy(b.posy),rayon(b.rayon){
	texture=IMG_Load("../ressources/game/bomb.png");
}


Bomb::~Bomb(){
	if(texture)
	SDL_FreeSurface(texture);
}

int Bomb::getPosX() const{
	return posx;
}

int Bomb::getPosY() const{
	return posy;
}

void Bomb::afficher(FenetreSDL * ecr){
	if(texture)
		ecr->blit(40+posx*40,60+posy*40,texture);
}

int Bomb::getRayon()const{
	return rayon;
}