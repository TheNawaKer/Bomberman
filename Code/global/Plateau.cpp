#include "Plateau.hpp"
#include "BlockFriable.hpp"

Plateau::Plateau(int dimx,int dimy):dimx(dimx),dimy(dimy){
	//joueur[1]=new Joueur()
	background=IMG_Load("../ressources/game/background.png");
}

void Plateau::ajouterBlock(int x,int y,int type){
	blocks.push_back(new BlockFriable(x,y));
}

void Plateau::DetruireBlock(int x,int y){
	for(int i=0;i<blocks.size();i++){
		if(blocks[i]->getPosX()==x && blocks[i]->getPosY()==y)
			blocks.erase(blocks.begin()+i);
	}
}

 void Plateau::ajouterBombe(int x,int y){
	//Bomb b(x,y);
	bombs.push_back(new Bomb(x,y));
 }

void Plateau::enleverBomb(int x,int y){
	for(int i=0;i<bombs.size();i++){
		if(bombs[i]->getPosX()==x && bombs[i]->getPosY()==y)
			bombs.erase(bombs.begin()+i);
	}
}


void Plateau::afficher(FenetreSDL * ecr){
	ecr->blit(0,0,background);
	for(int i=0; i <blocks.size(); ++i) 
		blocks[i]->afficher(ecr);

	for(int j =0; j<bombs.size(); ++j)
		bombs[j]->afficher(ecr);

}

bool Plateau::hasBlockOrBomb(int x,int y) const{
	for(int i=0; i <blocks.size(); ++i){
		if(blocks[i]->getPosX()==x && blocks[i]->getPosY()==y)
			return true;
	}

	for(int i=0; i <bombs.size(); ++i){
		if(bombs[i]->getPosX()==x && bombs[i]->getPosY()==y)
			return true;
	}

	return false;
}

int Plateau::getNbBlock() const{
	return blocks.size();
}

Block * Plateau::getBlock(int i){
	return blocks[i];
}

int Plateau::getNbBomb() const{
	return bombs.size();
}

Bomb * Plateau::getBomb(int i){
	return bombs[i];
}


Plateau::~Plateau(){
	if(background)
		SDL_FreeSurface(background);
}