#include "BlockFriable.hpp"

BlockFriable::BlockFriable(int x ,int y){
	posx=x;
	posy=y;
	resistance=1;
}

void BlockFriable::Briser(){
	resistance = 0;
}

void BlockFriable::Afficher(){
	if(resistance != 0){

	}
}