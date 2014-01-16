#include "../proto/Proto.hh"
#include "../global/FenetreSDL.hpp"
#include "../global/Plateau.hpp"
#include "../global/Joueur.hpp"
#include <pthread.h>
#include <iostream>
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
  int n;
  int i;

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
  }

  void on_begin();
  void do_err(string);
  void do_joined(int,int,string);
  void do_go(int,int,string);
  void do_board(int,int,int);
  void do_won(int);
  void do_moved(int,int,int);
  void do_explosion(int,int);
  void do_bomb(int,int);
  void do_die(int);
  void do_blockbreaked(int,int);
};


void * affichage( void *data )
{
  bomberman::session_on_client* s = (bomberman::session_on_client*)data;
  FenetreSDL fenetre(1280,720);
  SDL_Event event;
  bool quit=false;
    //Tant que l'utilisateur n'a pas quitté
  while(!quit)
  {
    s->plateau->afficher(&fenetre);
    fenetre.flip();
        //Tant qu'il y a un événement
    while( SDL_PollEvent( &event ) )
    {
            //Si l'utilisateur a cliqué sur le X de la fenêtre
      if( event.type == SDL_QUIT )
      {
                //On quitte the programme
        quit=true;
      }
    }
  }
}

void session_on_client::on_begin(){
  cout<<"Welcome to the bomberman game, please nick yourself"<<endl;
}

void session_on_client::do_err(string msg){
  cout<<msg<<endl;
}


void session_on_client::do_joined(int x,int y,string nick){
  cout<<nick<<" is now waiting for a game"<<endl;
  int i=1;
  while(!joueurs[i]){
    i++;
  }
  joueurs[i]=new Joueur(x,y,nick);
}

void session_on_client::do_go(int x,int y,string nick){
  if(state == WAITING_FOR_NICK){
    cout<<"You are now nicked , waiting for a game room"<<endl;
    plateau=new Plateau(30,16);
    joueurs[0]=new Joueur(x,y,nick);
    pthread_create (&thread, NULL, affichage, (void *)this);
    state = WAITING_FOR_GAME;
  }
}


void session_on_client::do_board(int x,int y,int type){
  cout<<"ajout d'un block en "<<x<<","<<y<<endl;
  plateau->ajouterBlock(x,y,type);
}

void session_on_client::do_won(int id){
  cout<<joueurs[id]->getNick()+" a gagné !!!"<<endl;
}


void session_on_client::do_moved(int posx,int posy,int id){
  joueurs[id]->setX(posx);
  joueurs[id]->setY(posy);
}


void session_on_client::do_explosion(int posx,int posy){
  plateau->enleverBomb(posx,posy);
}

void session_on_client::do_bomb(int posx,int posy){
  plateau->ajouterBombe(posx,posy);
}


void session_on_client::do_die(int id){

}

void session_on_client::do_blockbreaked(int posx,int posy){
  plateau->DetruireBlock(posx,posy);
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
  while(true){
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
      pthread_cancel(s.thread);
      break;
    }
  }
}




int main(int argc, char** argv)
{
  netez::client<bomberman::session_on_client> client(argc, argv);
  interaction_loop(client.session);
  client.join();
  return 0;
}
