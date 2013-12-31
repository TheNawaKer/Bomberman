#include "Proto.hh"
#include <iostream>

namespace bomberman
{
  using namespace std;
  using namespace netez;

  struct session_on_client: public session_base
  {
    enum state_t
      {
	STATE_STARTING   ,
	STATE_CONNECTING ,
	STATE_CONNECTED  ,
	STATE_TAKEN      ,
	STATE_MAYBEWAIT  ,
	STATE_WAITING    ,
	STATE_MAYBEPLAY
      };

    state_t state;
    int n;
    int i;

    session_on_client(socket& io): session_base(io), state(STATE_STARTING)
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
    }

    void on_begin();
    void do_err(string);
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

  }

  void session_on_client::do_err(string msg){

  }

  void session_on_client::do_go(){

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
int main(int argc, char** argv)
{
  netez::client<bomberman::session_on_client> client(argc, argv);
  client.join();
  return 0;
}
