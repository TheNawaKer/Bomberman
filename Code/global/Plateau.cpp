#include "Plateau.hpp"
#include "BlockFriable.hpp"

Plateau::Plateau(int dimx,int dimy):dimx(dimx),dimy(dimy){
	//joueur[1]=new Joueur()
	background=IMG_Load("background.png");
}

void Plateau::ajouterBlock(int x,int y,int type){
	Block * block = new BlockFriable(x,y);
	blocks.push_back(block);
}

void Plateau::DetruireBlock(int x,int y){
	for(int i=0;i<blocks.size();i++){
		if(blocks[i]->getPosX()==x && blocks[i]->getPosY()==y)
			blocks.erase(blocks.begin()+i);
	}
}

void Plateau::ajouterBombe(int x,int y){
	Bomb b(x,y);
	bombs.push_back(b);
}

void Plateau::enleverBomb(int x,int y){
	for(int i=0;i<bombs.size();i++){
		if(bombs[i].getPosX()==x && bombs[i].getPosY()==y)
			bombs.erase(bombs.begin()+i);
	}
}


void Plateau::afficher(FenetreSDL * ecr){
	ecr->blit(0,0,background);
	for(int i=0; i <blocks.size(); ++i) 
		blocks[i]->afficher(ecr);

	for(int j =0; j<bombs.size(); ++j)
		bombs[j].Afficher(ecr);

}

Plateau::~Plateau(){
	if(background)
		delete background;
}