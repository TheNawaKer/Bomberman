#ifndef _Block
#define _Block


class Block{
private:
	int posx;
	int posy;
public:
	virtual ~Block()=0;
	virtual void Briser()=0;
	virtual void Afficher()=0;

};



#endif