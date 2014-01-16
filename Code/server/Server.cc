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
    }
    void do_nick(string s);
    void do_quit();
    void do_move(int,int);
    void do_dropbomb(int,int);
    void send_board();
  };

  ezmutex the_mutex;
  map<int,session_on_server*> tab;
  Joueur * joueurs[4];
  Plateau * plateau;
  int nb;


  void init(){
    nb=0;
    plateau=new Plateau(30,15);
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
    it=tab.find(nb);
    for(int i=0;i<nb;i++){
        proto.Joined(joueurs[i]->getPosX(),joueurs[i]->getPosY(),joueurs[i]->getNick());
    }
    if(nb==1) 
      send_board();
    nb++;

  }
  else proto.Err("#error# This nick is already used.");
}

void session_on_server::do_quit(){
  //nettoyage map
  finish();
}

void session_on_server::send_board(){
  // plateau->ajouterBlock(0,0,0);
  plateau->ajouterBlock(5,0,0);
  vector<pair<int,int>> board;
  board.push_back(std::make_pair(5,0));
  // plateau->ajouterBlock(0,5,0);
  // plateau->ajouterBlock(2,2,0);
  // plateau->ajouterBlock(28,7,0);
  // plateau->ajouterBlock(18,4,0);
  auto it = tab.begin();
  while(it != tab.end()){
    it->second->proto.Board(board);
    ++it;
  }
}

void session_on_server::do_move(int posx,int posy){
  auto it(tab.begin());
  bool move=true;
  int id=0; //à déterminer;
  cout<<"move"<<endl;
  while(it != tab.end()){
    if(it->second==this)
      id=it->first;
    if(joueurs[it->first]->getPosX()==posx && joueurs[it->first]->getPosY()==posy){
      move=false;
      break;
    }
    it++;
  }
  if(move && !plateau->hasBlockOrBomb(posx,posy)){
   it = tab.begin();
   while(it != tab.end()){
    it->second->proto.Moved(posx,posy,joueurs[id]->getNick());
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
  bomberman::init();
  server.join();
  return 0;
}
