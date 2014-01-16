#include "BlockFriable.hpp"

BlockFriable::BlockFriable(int x ,int y){
	posx=x;
	posy=y;
	resistance=1;
	texture=IMG_Load("buisson.png");
}

BlockFriable::BlockFriable(BlockFriable & block){
	posx=block.posx;
	posy=block.posy;
	resistance=block.resistance;
	texture=IMG_Load("buisson.png");
}

void BlockFriable::Briser(){
	resistance = 0;
}