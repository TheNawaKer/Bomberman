#ifndef BLOCKTROISCOUP
#define BLOCKTROISCOUP

#include "Block.hpp"

class BlockTroiscoups: public Block{
public:
	BlockTroiscoups(int,int);
	virtual void Briser();
	virtual void Afficher(FenetreSDL * ecr);
};


#endif

