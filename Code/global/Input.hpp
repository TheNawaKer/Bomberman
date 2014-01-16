#ifndef _INPUT
#define _INPUT
#include <SDL/SDL.h>
class Input
{
protected:
    char key[SDLK_LAST];
    int mousex,mousey;
    int mousexrel,mouseyrel;
    int clicx,clicy;
    char mousebuttons[8];
    char quit;
public:
    Input();
    ~Input(){}
    void Update();
    inline char& Key(int i){return key[i];}
    inline int MouseX(){return mousex;}
    inline int MouseY(){return mousey;}
    inline int MouseXrel(){return mousexrel;}
    inline int MouseYrel(){return mouseyrel;}
    inline int ClicX(){return clicx;}
    inline int ClicY(){return clicy;}   
    inline char& MouseButton(int i){return mousebuttons[i];}
    inline int Quit(){return quit;}
};
 

#endif


