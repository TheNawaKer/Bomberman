#include "Block.hpp"

int Block::getPosX() const{
	return posx;
}

int Block::getPosY() const{
	return posy;
}

void Block::afficher(FenetreSDL * ecr){
	ecr->blit(40+posx,60+posy,texture);
}