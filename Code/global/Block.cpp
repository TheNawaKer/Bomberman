#include "Block.hpp"
#include <iostream>
using namespace std;

Block::Block(int x,int y, int res):posx(x),posy(y),resistance(res){}

Block::Block(Block & block):posx(block.posx),posy(block.posy),resistance(block.resistance){
	texture=IMG_Load("../ressources/game/buisson.png");
}

int Block::getPosX() const{
	return posx;
}

int Block::getPosY() const{
	return posy;
}

void Block::afficher(FenetreSDL * ecr){
	ecr->blit(40+posx*40,60+posy*40,texture);
}