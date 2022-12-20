#ifndef __IO_H__
#define __IO_H__

#include "../util/events.h"
#include "../util/common.h"
#include "json.hpp"
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

class IO {
  /*I think IO modules event will need const std::srting& path argument to 
  know what to read.
  Additionally I don't think wee need 2 different functions for this, since 
  information weather to read from file or webserver can be obtained from 
  scheme; IE file:// vs https://. */
  
  void write_event_function(const std::vector<PlanetData>& data, const std::string& filename){
    std::string str = serialize_file(data);
    write_file(str,filename);
  }

  std::vector<PlanetData> read_event_function(const std::string& filename){
    std::string data;
    if(filename.compare(0,4,"http")){
      data = read_web(filename);
      return parse_web(data);
    }else{
      data = read_file(filename);
      return parse_file(data);
    }
  }

  std::vector<PlanetData> parse_web(const std::string& data){

  }

  std::vector<PlanetData> parse_file(const std::string& data){

  }
  
  std::string serialize_file(const std::vector<PlanetData>& data){

  }

  std::string read_web(const std::string& path){

  }

  std::string read_file(const std::string& path){
    std::ifstream file(path);
    if(!file.is_open()){
      return "";
    }

    std::string ret;

    file.seekg(0, std::ios::end);
    size_t length = file.tellg();

    ret.resize(length);
    file.seekg(0, std::ios::beg);
    file.read(&ret[0],length);

    file.close();
    return ret;
  }

  bool write_file(const std::string& data, const std::string& path){
    std::ofstream file(path);
    if(!file.is_open()){
      return false;
    }
    file << data;
    file.close();
    return true;
  }

};

#endif // __IO_H__