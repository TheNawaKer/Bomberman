#ifndef BLOCKINCASSABLE
#define BLOCKINCASSABLE

#include "Block.hpp"

class BlockIncassable: public Block{
public:
	BlockIncassable(int,int);
	virtual void Briser();
};

#endif