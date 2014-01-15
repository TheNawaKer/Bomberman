#include "FenetreSDL.hpp"
using namespace std; 


FenetreSDL::FenetreSDL(int l, int h){
  this->h=h;
  this->l=l;
  SDL_Init(SDL_INIT_VIDEO); // initialisation mode graphique 
  ecr = SDL_SetVideoMode(l, h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); 
  SDL_WM_SetCaption("Bomberman", NULL); 
}


void FenetreSDL::vider(){
  blit(0,0,l,h,NULL);
}

void FenetreSDL::flip(){
  SDL_Flip(ecr);
}

FenetreSDL::~FenetreSDL(){
  SDL_FreeSurface(ecr);
  SDL_Quit();
}


int FenetreSDL::getL() const{
  return l;
}
int FenetreSDL::getH() const{
  return h;
}

void FenetreSDL::blit(int x,int y,int lsurf,int hsurf,SDL_Surface *surf){
  SDL_Rect rect={x,y,lsurf,hsurf};
  SDL_BlitSurface(surf,NULL,ecr,&rect);
}

void FenetreSDL::blit(int x,int y,SDL_Surface *surf){
  SDL_Rect rect;
  rect.x=x;
  rect.y=y;
  SDL_BlitSurface(surf,NULL,ecr,&rect);
}