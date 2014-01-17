#include "../proto/Proto.hh"
#include "../global/FenetreSDL.hpp"
#include "../global/Plateau.hpp"
#include "../global/Joueur.hpp"

#include "../global/Input.hpp"
#include <pthread.h>
#include <iostream>
#include <sstream>
using namespace std;

namespace bomberman
{
  using namespace std;
  using namespace netez;

  enum state_t
  {
   BEGIN,
   WAITING_FOR_NICK,
   WAITING_FOR_GAME,
   IN_GAME,
   DEAD
 };

 struct session_on_client: public session_base
 {


  state_t state;
  pthread_t thread;
  Plateau * plateau;
  Joueur * joueurs[4];
  bool quit;

  session_on_client(socket& io): session_base(io), state(BEGIN)
  {
    sig_begin.connect(EZMETHOD(this,on_begin));
    proto.Err.sig_recv.connect(EZMETHOD(this,do_err));
    proto.Go.sig_recv.connect(EZMETHOD(this,do_go));
    proto.Board.sig_recv.connect(EZMETHOD(this,do_board));
    proto.Won.sig_recv.connect(EZMETHOD(this,do_won));
    proto.Moved.sig_recv.connect(EZMETHOD(this,do_moved));
    proto.Explosion.sig_recv.connect(EZMETHOD(this,do_explosion));
    proto.Bomb.sig_recv.connect(EZMETHOD(this,do_bomb));
    proto.Die.sig_recv.connect(EZMETHOD(this,do_die));
    proto.BlockBreaked.sig_recv.connect(EZMETHOD(this,do_blockbreaked));
    proto.Joined.sig_recv.connect(EZMETHOD(this,do_joined));
    proto.Quit.sig_recv.connect(EZMETHOD(this,do_quit));
  }

  void on_begin();
  void do_err(string);
  void do_joined(int,int,string);
  void do_go(int,int,string);
  void do_board(vector<pair<int,int>>);
  void do_won(int);
  void do_moved(int,int,string);
  void do_explosion(int,int);
  void do_bomb(int,int);
  void do_die(string);
  void do_blockbreaked(int,int);
  void do_quit();
};


void * affichage( void *data )
{
  bomberman::session_on_client* s = (bomberman::session_on_client*)data;
  FenetreSDL fenetre(1280,720);
  Input in;
    //Tant que l'utilisateur n'a pas quitté
  while(!s->quit)
  {
    s->plateau->afficher(&fenetre);
    for(int i=0;i<4;i++){
      if(s->joueurs[i]){
        s->joueurs[i]->afficher(&fenetre);
      }
    }

    fenetre.flip();
        //Tant qu'il y a un événement
    if(s->state == bomberman::IN_GAME){
      in.Update();
      if(in.Key(SDLK_UP)){ in.Key(SDLK_UP)=0; s->proto.Move(s->joueurs[0]->getPosX(),s->joueurs[0]->getPosY()-1); }
      if(in.Key(SDLK_DOWN)){ in.Key(SDLK_DOWN)=0; s->proto.Move(s->joueurs[0]->getPosX(),s->joueurs[0]->getPosY()+1); }
      if(in.Key(SDLK_RIGHT)){ in.Key(SDLK_RIGHT)=0; s->proto.Move(s->joueurs[0]->getPosX()+1,s->joueurs[0]->getPosY()); }
      if(in.Key(SDLK_LEFT)){ in.Key(SDLK_LEFT)=0; s->proto.Move(s->joueurs[0]->getPosX()-1,s->joueurs[0]->getPosY()); }
      if(in.Key(SDLK_SPACE)){ in.Key(SDLK_SPACE)=0; s->proto.DropBomb(s->joueurs[0]->getPosX(),s->joueurs[0]->getPosY()); }
      if(in.Quit()){ s->proto.Quit(); s->quit=true; }
      
    }
  }
}

void session_on_client::on_begin(){
  cout<<"Welcome to the bomberman game, please nick yourself"<<endl;
  for(int i=0;i<4;i++){
    joueurs[i]=NULL;
  }
}

void session_on_client::do_err(string msg){
  cout<<msg<<endl;
}


void session_on_client::do_joined(int x,int y,string nick){
  cout<<nick<<" is now waiting for a game"<<endl;
  int i=1;
  while(joueurs[i]!=NULL){
    i++;
  }
  std::ostringstream oss;
  oss << "persoG" << i+1;
  joueurs[i]=new Joueur(x,y,nick,oss.str());
}

void session_on_client::do_go(int x,int y,string nick){
  if(state == WAITING_FOR_NICK){
    cout<<"You are now nicked , waiting for a game room"<<endl;
    joueurs[0]=new Joueur(x,y,nick,"persoD1");
    state = WAITING_FOR_GAME;
  }
}


void session_on_client::do_board(vector<pair<int,int>> board){
  plateau=new Plateau(30,15);
  for(int i=0;i<board.size();i++){
    cout<<"ajout d'un block en "<<board[i].first<<","<<board[i].second<<endl;
    plateau->ajouterBlock(board[i].first,board[i].second,0);
  }
  pthread_create(&thread, NULL, affichage, (void *)this);
  state=IN_GAME;

  
}

void session_on_client::do_won(int id){
  cout<<joueurs[id]->getNick()+" a gagné !!!"<<endl;
}


void session_on_client::do_moved(int posx,int posy,string nick){
  for(int i=0;i<4;i++){
    if(joueurs[i]!=NULL && joueurs[i]->getNick()==nick){
      joueurs[i]->setX(posx);
      joueurs[i]->setY(posy);
      break;
    }
  }

}


void session_on_client::do_explosion(int posx,int posy){
  plateau->enleverBomb(posx,posy);
}

void session_on_client::do_bomb(int posx,int posy){
  plateau->ajouterBombe(posx,posy);
}


void session_on_client::do_die(string nick){
  if(joueurs[0]->getNick()==nick)
      state = DEAD;
  for(int i=0;i<4;i++){
    if(joueurs[i]->getNick()==nick){
      delete joueurs[i];
      break;
    }
  }
}

void session_on_client::do_blockbreaked(int posx,int posy){
  plateau->DetruireBlock(posx,posy);
}

void session_on_client::do_quit(){
  proto.Quit();
  finish();
}

}


//enleve les espaces au deux bout d'une chaine
string strip( string & s)
{

  size_t i = s. find_first_not_of (" \t");
  if (i == string :: npos) return "";
  size_t j = s. find_last_not_of (" \t");
  return s. substr (i,j-i+1);
}

// boucle d’interaction qui utilise les methodes
// cli. session . cmd_YYY (...) pour executer les
// commandes saisies par l’utilisateur 
void interaction_loop(bomberman::session_on_client & s){
  string line;
  s.quit=false;
  while(!s.quit){
    cout<<"boucle"<<endl;
    getline(cin,line);
    string cmd;
    istringstream is(line);
    is>>cmd;

    if(cmd == "/nick"){
      string nick;
      is>>nick;
      s.proto.Nick(nick);
      s.state = bomberman::WAITING_FOR_NICK;
    }else if(cmd == "/quit"){
      s.proto.Quit();
      s.quit=true;
      break;
    }
}
  pthread_join(s.thread,NULL);
}




int main(int argc, char** argv)
{
  netez::client<bomberman::session_on_client> client(argc, argv);
  interaction_loop(client.session);
  client.join();
  return 0;
}
