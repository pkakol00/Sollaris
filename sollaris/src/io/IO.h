#ifndef __IO_H__
#define __IO_H__

#include "../util/events.h"
#include "../util/common.h"
#include <vector>

class IO {
  /*I think IO modules event will need const std::srting& path argument to 
  know what to read.
  Additionally I don't think wee need 2 different functions for this, since 
  information weather to read from file or webserver can be obtained from 
  scheme; IE file:// vs https://. */
  
  CREATE_EVENT(read, std::vector<PlanetData>, const std::string&);
  CREATE_EVENT(write, void, std::vector<PlanetData>, const std::string&)
};

#endif // __IO_H__