#include "../proto/Proto.hh"
#include "../global/Plateau.hpp"
#include "../global/Joueur.hpp"
#include <iostream>

namespace bomberman
{
  using namespace std;
  using namespace netez;



  struct session_on_server: public session_base
  {
    session_on_server(socket& io): session_base(io)
    {
      proto.Nick.sig_recv.connect(EZMETHOD(this,do_nick));
      proto.Quit.sig_recv.connect(EZMETHOD(this,do_quit));
      proto.Move.sig_recv.connect(EZMETHOD(this,do_move));
      proto.DropBomb.sig_recv.connect(EZMETHOD(this,do_dropbomb));
      proto.Explosion.sig_recv.connect(EZMETHOD(this,do_explode));
    }
    void do_nick(string s);
    void do_quit();
    void do_move(int,int);
    void do_dropbomb(int,int);
    void do_explode(int,int);
    vector<pair<int,int>> send_board();
  };

  ezmutex the_mutex;
  map<int,session_on_server*> tab;
  Joueur * joueurs[4];
  Plateau * plateau;
  Bomb * bomb;
  int nb;


  void init(){
    nb=0;
    bomb=NULL;
    plateau=new Plateau(30,15);
    plateau->ajouterBlock(5,0,0);
    cout<<"Demarrage du serveur"<<endl;
  }

  void session_on_server::do_nick(string nick){
    ezlock hold(the_mutex);
    bool find=false;
    for(int i=0;i<nb;i++){
      if(joueurs[i]){
        if(joueurs[i]->getNick()==nick){
          find=true;
          break;
        }
      }
    }

    if(!find && nb<4){
     tab[nb]=this;

     int x,y;
    //attribution de la position de départ en fonction du numéro du joueur
     switch(nb){
      case 0:
      x=0;
      y=0;
      break;
      case 1:
      x=29;
      y=14;
      break;
      case 2:
      x=0;
      y=14;
      break;
      case 3:
      x=29;
      y=0;
      break;
    }

    joueurs[nb]=new Joueur(x,y,nick);
    proto.Go(x,y,nick);


    auto it(tab.begin());
    while(it != tab.end()){
      if(it->first != nb) it->second->proto.Joined(x,y,nick);
      ++it;
    }
    for(int i=0;i<nb;i++){
      proto.Joined(joueurs[i]->getPosX(),joueurs[i]->getPosY(),joueurs[i]->getNick());
    }
    if(nb==1) 
    {  
      auto it = tab.begin();
      while(it != tab.end()){
        it->second->proto.Board(send_board());
        ++it;
      }
    }
    else if(nb>1){
     proto.Board(send_board());
   }
   nb++;

 }
 else proto.Err("#error# This nick is already used.");
}

void session_on_server::do_quit(){
  ezlock hold(the_mutex);
  //nettoyage map
  finish();
}

vector<pair<int,int>> session_on_server::send_board(){
  ezlock hold(the_mutex);
  
  vector<pair<int,int>> board;
  for(int i=0;i<plateau->getNbBlock();i++){
    board.push_back(std::make_pair(plateau->getBlock(i)->getPosX(),plateau->getBlock(i)->getPosY()));
  }
  return board;

}

void session_on_server::do_move(int posx,int posy){
  ezlock hold(the_mutex);

  // entre la case 0 et la case 30
  if((posx>=0 && posx<=30)&&(posy>=0 && posy<=15)){
    auto it(tab.begin());
    bool move=true;
  int id=0; //à déterminer;
  while(it != tab.end()){
    if(it->second==this)
      id=it->first;
    //collision avec un joueur
    if(joueurs[it->first]->getPosX()==posx && joueurs[it->first]->getPosY()==posy){
      move=false;
      break;
    }
    ++it;
  }
  if(move && !plateau->hasBlockOrBomb(posx,posy)){
   it = tab.begin();
   while(it != tab.end()){
    it->second->proto.Moved(posx,posy,joueurs[id]->getNick());
    ++it;
  }
}
}
}

void session_on_server::do_dropbomb(int posx,int posy){
  ezlock hold(the_mutex);

  if(bomb==NULL){
      //on ajoute la bombe
    plateau->ajouterBombe(posx,posy);
    bomb=new Bomb(posx,posy);
    //on envoie le position de la bombe à tout les joueurs

    auto it = tab.begin();
    while(it != tab.end()){
      it->second->proto.Bomb(posx,posy);
      ++it;
    }
  }

}

void session_on_server::do_explode(int x,int y){
  if(bomb){
    // si la bombe 
    if(bomb->getPosX()== x && bomb->getPosY()== y){
     auto it = tab.begin();
     while(it != tab.end()){

      it->second->proto.Explosion(x,y);
      ++it;
    }
     delete bomb;
     bomb=NULL;
     plateau->enleverBomb(x,y);

     //gestion l'explosion vers la gauche
     int rayon = bomb->getRayon();
     for(int i =x; i >= 0 && i >= x-rayon; ++i){ 
      if(plateau->hasBlockOrBomb(i,y)){ 
        auto it = tab.begin();
        while(it != tab.end()){
          it->second->proto.BlockBreaked(i,y);
        }
      }
    }


         //gestion l'explosion vers la droite

     for(int i =x; i <= 29 && i <= x+rayon; ++i){ 
      if(plateau->hasBlockOrBomb(i,y)){ 
        auto it = tab.begin();
        while(it != tab.end()){
          it->second->proto.BlockBreaked(i,y);
        }
      }
    }

             //gestion l'explosion vers le haut

     for(int i =y; i >= 0 && i >= x-rayon; ++i){ 
      if(plateau->hasBlockOrBomb(x,i)){ 
        auto it = tab.begin();
        while(it != tab.end()){
          it->second->proto.BlockBreaked(x,i);
        }
      }
    }

                 //gestion l'explosion vers le bas

     for(int i =y; i <= 15  && i <= x+rayon; ++i){ 
      if(plateau->hasBlockOrBomb(x,i)){ 
        auto it = tab.begin();
        while(it != tab.end()){
          it->second->proto.BlockBreaked(x,i);
        }
      }
    }




  }

}

}



}


int main(int argc, char** argv)
{
  netez::server<bomberman::session_on_server> server(argc, argv);
  bomberman::init();
  server.join();
  return 0;
}
