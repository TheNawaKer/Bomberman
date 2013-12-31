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

    }

  };


}


int main(int argc, char** argv)
{
  netez::server<bomberman::session_on_server> server(argc, argv);
  server.join();
  return 0;
}
