#include "Proto.hh"
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
    void do_move(int,int,int);
    void do_dropbomb(int,int);
  };





void session_on_server::do_nick(string s){

}

void session_on_server::do_quit(){

}

void session_on_server::do_move(int posx,int posy,int id){

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
