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
     // sig_begin          .connect(EZMETHOD(this,on_begin));
    }

    //void on_begin();
};

 // void session_on_client::on_begin();


}
int main(int argc, char** argv)
{
  netez::client<bomberman::session_on_client> client(argc, argv);
  client.join();
  return 0;
}
