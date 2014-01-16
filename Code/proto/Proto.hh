#ifndef _BOMBER_PROTO_
#define _BOMBER_PROTO_

#include "netez.hh"
#include <iostream>

namespace bomberman
{
  using namespace netez;

  struct proto_bomber: public protocol<>
  {
    message<0,void()            > Connecting;
    message<1,void()             > Connected;
    message<2,void(std::string)       > Nick;
    message<3,void(std::string)        > Err;
    message<4,void(int,int,std::string) > Go;
    message<5,void(int,int,int)                 > Board;
    message<6,void(int,int)       > Move;
    message<7,void(int,int,int)      > Moved;
    message<8,void(int,int)        > DropBomb;
    message<9,void(int)                > Won;
    message<10,void()                 > Quit;
    message<11,void(int,int)     > Explosion;
    message<12,void(int,int)          > Bomb;
    message<13,void(int)           > Die;
    message<14,void(int,int)  > BlockBreaked;
    message<15,void(int,int,std::string)    > Joined;

    proto_bomber(socket& io)
      : protocol<>(io),
	Connecting(this),
	Connected (this),
	Nick      (this),
	Err       (this),
	Go        (this),
	Board     (this),
	Move      (this),
	Moved     (this),
	DropBomb   (this),
	Won       (this),
  Quit      (this),
  Explosion (this),
  Bomb      (this),
  Die       (this),
  BlockBreaked (this),
  Joined    (this)
    {}
  };

  typedef session<proto_bomber> session_base;
}

#endif