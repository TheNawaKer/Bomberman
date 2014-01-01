#ifndef _NETEZ_EXTRA_HH_
#define _NETEZ_EXTRA_HH_

#include "netez.hh"
#include <list>
#include <vector>
#include <map>

namespace netez
{
  template <typename T>
  struct serializable<std::list<T> >
  {
    static inline void put(std::ostream& os, const std::list<T>& x)
    {
      uint32_t n = x.size();
      serializable_put(os,n);
      auto beg(x.begin()), end(x.end());
      while (beg != end) { serializable_put(os,*beg); ++beg; }
    }
    static inline void get(std::istream& is, std::list<T>& x)
    {
      uint32_t n;
      serializable_get(is,n);
      while (n) { T y; serializable_get(is,y); x.push_back(y); --n; }
    }
  };

  template <typename T>
  struct serializable<std::vector<T> >
  {
    static inline void put(std::ostream& os, const std::vector<T>& x)
    {
      uint32_t n = x.size();
      serializable_put(os,n);
      auto beg(x.begin()), end(x.end());
      while (beg != end) { serializable_put(os,*beg); ++beg; }
    }
    static inline void get(std::istream& is, std::vector<T>& x)
    {
      uint32_t n;
      serializable_get(is,n);
      while (n) { T y; serializable_get(is,y); x.push_back(y); --n; }
    }
  };

  template <typename T1, typename T2>
  struct serializable<std::pair<T1,T2> >
  {
    static inline void put(std::ostream& os, const std::pair<T1,T2>& x)
    {
      serializable_put(os, x.first);
      serializable_put(os, x.second);
    }
    static inline void get(std::istream& is, std::pair<T1,T2>& x)
    {
      serializable_get(is,x.first);
      serializable_get(is,x.second);
    }
  };

  template <typename T1, typename T2>
  struct serializable<std::map<T1,T2> >
  {
    static inline void put(std::ostream& os, const std::map<T1,T2>& x)
    {
      uint32_t n = x.size();
      serializable_put(os,n);
      auto beg(x.begin()), end(x.end());
      while (beg != end) { serializable_put(os,*beg); ++beg; }
    }
    static inline void get(std::istream& is, std::map<T1,T2>& x)
    {
      uint32_t n;
      serializable_get(is,n);
      while (n) { std::pair<T1,T2> y; serializable_get(is,y); x.insert(y); --n; }
    }
  };
};

#endif
