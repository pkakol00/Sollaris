#include "../util/events.h"
#include "../util/common.h"
#include "IO.h"
#include "json.hpp"
#include <cstdio>
#include <fstream>
#include <string>
#include <type_traits>
#include <vector>
#include <curl/curl.h>

using json = nlohmann::json;

  void IO::write_event(const std::vector<PlanetData>& data, const std::string& filename){
    std::string str = serialize_file(data);
    write_file(str,filename);
  }

  std::vector<PlanetData> IO::read_event(const std::string& filename){
    std::string data;
    if(filename.compare(0,4,"http")==0){
      return get_web(filename);
      // data = read_web(filename);
      // return parse_web(data);
    }else{
      data = read_file(filename);
      return parse_file(data);
    }
  }

  PlanetData IO::parse_web(const std::string& data){
    int pos=0;
    Vec3 position;
    PlanetData planet;
    pos = data.find("Mean Radius (km) =",pos) + 18;
    planet.radious = atof(data.c_str()+pos);
    pos = data.find("Mass x10^",pos) + 9;
    int multi = atoi(data.c_str()+pos);
    pos = data.find("=",pos) + 1;
    planet.mass = atof(data.c_str()+pos) * pow(10,multi);
    pos = data.find("X =",pos) + 3;
    position.x = atof(data.c_str()+pos);
    pos = data.find("Y =",pos) + 3;
    position.y = atof(data.c_str()+pos);
    pos = data.find("Z =",pos) + 3;
    position.z = atof(data.c_str()+pos);
    pos = data.find("VX=",pos) + 3;
    planet.velocity.x = atof(data.c_str()+pos);
    pos = data.find("VY=",pos) + 3;
    planet.velocity.y = atof(data.c_str()+pos);
    pos = data.find("VZ=",pos) + 3;
    planet.velocity.z = atof(data.c_str()+pos);
    return planet;
  }

  std::vector<PlanetData> IO::get_web(const std::string& path){

    std::cerr<<"web"<<std::endl;

    std::string req;
    std::string data;

    const int solar_size = 10;
    std::vector<PlanetData> planets(solar_size);
    std::array<std::string,solar_size> solar_names={
      "Mercury",
      "Venus",
      "Earth",
      "Mars",
      "Saturn",
      "Jowisz",
      "Uran",
      "Neptun",
      "Pluto",
      "Sun"
    };



      //"https://ssd.jpl.nasa.gov/api/horizons.api?EPHEM_TYPE=VECTORS&COMMAND='0'&STEP_SIZE='1d'&START_TIME='2023-01-25 00:00'&STOP_TIME='2023-01-25 12:00'&VEC_TABLE=2&CENTER='@0'"
    for(int i=0;i<solar_size;i++){
      req="https://ssd.jpl.nasa.gov/api/horizons.api?COMMAND='";
      req+=i;
      req+="'&format=text&EPHEM_TYPE=VECTORS&STEP_SIZE='1d'&START_TIME='2023-01-25 00:00'&STOP_TIME='2023-01-25 12:00'&VEC_TABLE=2&CENTER='@0'";
      planets.push_back(parse_web(data));

    }

    return planets;
  }

  std::vector<PlanetData> IO::parse_file(const std::string& data){
    json load = json::parse(data);
    std::vector<PlanetData> ret;
    ret.resize(load.size());


    for(int i=0;i<load.size();i++){
      ret[i].mass = load[i]["mass"];
      ret[i].radious = load[i]["radious"] ;
      ret[i].velocity.x = load[i]["velocity"][0];
      ret[i].velocity.y = load[i]["velocity"][1];
      ret[i].velocity.z = load[i]["velocity"][2];
      ret[i].velocity.x = load[i]["colour"][0];
      ret[i].velocity.y = load[i]["colour"][1];
      ret[i].velocity.z = load[i]["colour"][2];
      ret[i].planet_id = load[i]["planet_id"] ;
    }

    return ret;

  }

  std::string IO::serialize_file(const std::vector<PlanetData>& data){
    json save;
    for(int i=0;i<data.size();i++){
      save[i]["mass"] = data[i].mass;
      save[i]["radious"] = data[i].radious;
      save[i]["velocity"] = {data[i].velocity.x,data[i].velocity.y,data[i].velocity.z};
      save[i]["colour"] = {data[i].colour.x,data[i].colour.y,data[i].colour.z};
      save[i]["planet_id"] = data[i].planet_id;
    }
    return save.dump();
  }

 

  std::string IO::read_web(const std::string& path){
    return "";
  }

  std::string IO::read_file(const std::string& path){
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

  bool IO::write_file(const std::string& data, const std::string& path){
    std::ofstream file(path);
    if(!file.is_open()){
      return false;
    }
    file << data;
    file.close();
    return true;
  }