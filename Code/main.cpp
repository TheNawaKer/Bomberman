#include "global/FenetreSDL.hpp"
#include "global/Plateau.hpp"
#include <iostream>
using namespace std;

int main(){
	FenetreSDL fenetre(1280,720);
	Plateau plateau;
	plateau.afficher(&fenetre);
	fenetre.flip();
	int i;
	cin>>i;
	return 0;
}
