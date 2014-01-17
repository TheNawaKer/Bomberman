#include "BlockFriable.hpp"
#include <iostream>
using namespace std;

BlockFriable::BlockFriable(int x ,int y):Block(x,y,1){
	texture=IMG_Load("../ressources/game/buisson.png");
}

void BlockFriable::Briser(){
	resistance = 0;
}