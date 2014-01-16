#ifndef BLOCKFRIABLE
#define BLOCKFRIABLE

#include "Block.hpp"

class BlockFriable: public Block{
public:
	BlockFriable(int,int);
	BlockFriable(BlockFriable & block);
	virtual void Briser();
};


#endif

