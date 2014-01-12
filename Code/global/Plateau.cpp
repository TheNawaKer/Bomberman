#include "Plateau.hpp"

Plateau::Plateau(){
	//joueur[1]=new Joueur()
	background=IMG_Load("background.png");
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


void Plateau::Afficher(FenetreSDL * ecr){
	//backgroung
	for(int i=0; i <blocks.size(); ++i) 
		blocks[i]->Afficher(ecr);

	for(int j =0; j<bombs.size(); ++j)
		bombs[j].Afficher(ecr);

}