#ifndef _FENETRE
#define _FENETRE
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

class FenetreSDL{
  int h;
  int l;
public:
  SDL_Surface *ecr; 
  FenetreSDL(int,int);
  void vider();
  void flip();  
  ~FenetreSDL();
  int getL()const;
  int getH()const;
  void blit(int,int,int,int,SDL_Surface*);
  void blit(int x,int y,SDL_Surface *surf);
};



#endif