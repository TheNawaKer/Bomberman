#ifndef _BOMBER_PROTO_
#define _BOMBER_PROTO_

#include "netez.hh"
#include <iostream>

namespace bomberman
{
  using namespace netez;

  struct proto_bomber: public protocol<>
  {
    message<0,void()   > connecting;
    message<1,void()   > connected;
    message<2,void(std::string)   > nick;
    message<3,void()   > play;
    message<4,void(int)> take;
    message<5,void()   > ok;
    message<6,void()   > err;
    message<7,void(int)> took;
    message<8,void()   > lost;
    message<9,void()   > won;

    proto(socket& io)
      : protocol<>(io),
	connecting(this),
	connected (this),
	nick      (this),
	play      (this),
	take      (this),
	ok        (this),
	err       (this),
	took      (this),
	lost      (this),
	won       (this)
    {}
  };

  typedef session<proto_bomber> session_base;
}

#endif