#include "Bomb.hpp"



Bomb::Bomb(int x, int y):posx(x),posy(y),rayon(1){

}


Bomb::Bomb(int x, int y,int r):posx(x),posy(y),rayon(r){
	
}

Bomb::~Bomb(){
	SDL_FreeSurface(texture);
}

int Bomb::getPosX() const{
	return posx;
}

int Bomb::getPosY() const{
	return posy;
}