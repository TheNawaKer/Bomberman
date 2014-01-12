#ifndef BLOCKFRIABLE
#define BLOCKFRIABLE

#include "Block.hpp"

class BlockFriable: public Block{
public:
	BlockFriable(int,int);
	virtual void Briser();
	virtual void Afficher(FenetreSDL * ecr);
};


#endif

