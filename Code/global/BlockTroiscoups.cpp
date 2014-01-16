#include "BlockTroiscoups.hpp"

BlockTroiscoups::BlockTroiscoups(int x ,int y):Block(x,y,3){}

void BlockTroiscoups::Briser(){
	--resistance;
}