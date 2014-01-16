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
      sig_begin.connect(EZMETHOD(this,do_begin));
      proto.Nick.sig_recv.connect(EZMETHOD(this,do_nick));
      proto.Quit.sig_recv.connect(EZMETHOD(this,do_quit));
      proto.Move.sig_recv.connect(EZMETHOD(this,do_move));
      proto.DropBomb.sig_recv.connect(EZMETHOD(this,do_dropbomb));
    }
    void do_begin();
    void do_nick(string s);
    void do_quit();
    void do_move(int,int,int);
    void do_dropbomb(int,int);
  };

  ezmutex the_mutex;
  map<int,session_on_server*> tab;
  Joueur * joueurs[4];
  Plateau * plateau;
  int nb;


void session_on_server::do_begin(){
  nb=-1;
  plateau=new Plateau(30,16);
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
    //auto it(tab.find(nick));
    if(!find){
      //add nick to the map
     tab[nb]=this;
     joueurs[nb]=new Joueur(0,0,nick);
     proto.Go();


    auto it(tab.begin());
    while(it != tab.end()){
      //tell everyone (exept nick) that 'nick' is here
      if(it->first != nb) it->second->proto.Joined(joueurs[nb]->getNick());
      ++it;
    }
    nb++;

   }
    else proto.Err("#error# This nick is already used.");
}

void session_on_server::do_quit(){
  finish();
}

void session_on_server::do_move(int posx,int posy,int id){
  auto it(tab.begin());
  bool move=true;
    while(it != tab.end()){
      //tell everyone (exept nick) that 'nick' is here
      if(it->first!=id && joueurs[it->first]->getPosX()==posx && joueurs[it->first]->getPosY()==posy){
        move=false;
        break;
      }
      it++;
    }
    if(move){
       it = tab.begin();
      while(it != tab.end()){
        it->second->proto.Moved(posx,posy,id);
        ++it;
      }
    }
}

void session_on_server::do_dropbomb(int posx,int posy){
}


}


int main(int argc, char** argv)
{
  netez::server<bomberman::session_on_server> server(argc, argv);
  server.join();
  return 0;
}
