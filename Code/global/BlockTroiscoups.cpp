#include "BlockTroiscoups.hpp"

BlockTroiscoups::BlockTroiscoups(int x ,int y){
	posx=x;
	posy=y;
	resistance=3;
}

void BlockTroiscoups::Briser(){
	--resistance;
}

void BlockTroiscoups::Afficher(){
	if(resistance != 0){
		
	}
}