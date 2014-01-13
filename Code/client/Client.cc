#include "../proto/Proto.hh"
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
    void do_joined(string);
    void do_go();
    void do_board();
    void do_won(int);
    void do_moved(int,int,int);
    void do_explosion(int,int);
    void do_bomb(int,int);
    void do_die(int);
    void do_blockbreaked(int,int);
};



  void session_on_client::on_begin(){
    cout<<"Welcome to the bomberman game, please nick yourself"<<endl;
  }

  void session_on_client::do_err(string msg){
    cout<<msg<<endl;
  }


  void session_on_client::do_joined(string nick){
    cout<<nick<<" is now waiting for a game"<<endl;
  }

  void session_on_client::do_go(){
    if(state == WAITING_FOR_NICK){
      cout<<"You are now nicked , waiting for a game room"<<endl;
      state = WAITING_FOR_GAME;
    }
  }


  void session_on_client::do_board(){

  }

  void session_on_client::do_won(int id){

  }


  void session_on_client::do_moved(int posx,int posy,int id){

  }


  void session_on_client::do_explosion(int posx,int posy){

  }

  void session_on_client::do_bomb(int posx,int posy){

  }


  void session_on_client::do_die(int id){

  }

  void session_on_client::do_blockbreaked(int posx,int posy){

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
  while(1){
    getline(cin,line);
    string cmd;
    istringstream is(line);
    is>>cmd;

    if(cmd == "/nick"){
      string nick;
      is>>nick;
      s.proto.Nick(nick);
      s.state = bomberman::WAITING_FOR_NICK;
    } 

    else if(cmd == "/quit"){
        s.proto.Quit();
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
