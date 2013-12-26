#ifndef _Block
#define _Block


class Block{
protected:
	int posx;
	int posy;
	int resistance;
public:
	virtual ~Block()=0;
	virtual void Briser()=0;
	virtual void Afficher()=0;

};


class BlockIncassable : public Block{
public:
	BlockIncassable(int,int);
	virtual void Briser();
	virtual void Afficher();
};


#endif