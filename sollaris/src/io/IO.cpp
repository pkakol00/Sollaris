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

  void IO::write_event(std::vector<PlanetData> data1, std::vector<PlanetPosition> data2, const std::string& filename){
    std::ofstream file(filename,std::ios::binary);
    std::string ser;
    std::size_t size;
    if(!file.is_open()){
      throw;
    }
    for(int i = 0; i<data1.size();i++){
      ser = data1[i].serialize();
      size = ser.size();
      file.write((char*)(&size),sizeof(ser.size()));
      file.write(ser.data(),ser.size());
      ser = data2[i].serialize();
      size = ser.size();
      file.write((char*)(&size),sizeof(ser.size()));
      file.write(ser.data(),ser.size());
    }
    file.close();
    // std::string str = serialize_file(data);
    // std::cerr<<str<<std::endl;
    // write_file(str,filename);
  }

  void IO::read_event(std::vector<PlanetData>& data1, std::vector<PlanetPosition>& data2, const std::string& filename){
    // std::string data;
    // if(filename.compare(0,4,"http")==0){
    //   return get_web(filename);
    //   // data = read_web(filename);
    //   // return parse_web(data);
    // }else{
      return read_file(data1,data2,filename);
      // data = read_file(filename);
      // return parse_file(data);
    // }
  }

  void IO::parse_web(PlanetData &planet, PlanetPosition& pposition, const std::string& data){
    int pos=0;
    Vec3 position;
    pos = data.find("Mean Radius (km)",0) + 16;
    pos = data.find("=",pos) + 1;
    planet.radious = atof(data.c_str()+pos)*1000;
    pos = data.find("Mass x10^",0) + 9;
    int multi = atoi(data.c_str()+pos);
    pos = data.find("=",pos) + 1;
    planet.mass = atof(data.c_str()+pos) * pow(10,multi);
    pos = data.find("X =",pos) + 3;
    position.x = atof(data.c_str()+pos)*1000;
    pos = data.find("Y =",pos) + 3;
    position.y = atof(data.c_str()+pos)*1000;
    pos = data.find("Z =",pos) + 3;
    position.z = atof(data.c_str()+pos)*1000;
    pos = data.find("VX=",pos) + 3;
    planet.velocity.x = atof(data.c_str()+pos)*1000;
    pos = data.find("VY=",pos) + 3;
    planet.velocity.y = atof(data.c_str()+pos)*1000;
    pos = data.find("VZ=",pos) + 3;
    planet.velocity.z = atof(data.c_str()+pos)*1000;
    pposition.positions.push_back(position);
    // std::cout << "in io: " << position.x << std::endl;
  }







  static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
  {
      ((std::string*)userp)->append((char*)contents, size * nmemb);
      return size * nmemb;
  }

  void IO::get_web(std::vector<PlanetData>& data1, std::vector<PlanetPosition>& data2, std::string date){
    std::string req;
    std::string data;

    const int solar_size = 10;
    data1.clear();
    data2.clear();
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

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    if(date == ""){
      date = "2023-01-25";
    }

    //"https://ssd.jpl.nasa.gov/api/horizons.api?EPHEM_TYPE=VECTORS&COMMAND='0'&STEP_SIZE='1d'&START_TIME='2023-01-25 00:00'&STOP_TIME='2023-01-25 12:00'&VEC_TABLE=2&CENTER='@0'"
    //+https://ssd.jpl.nasa.gov/api/horizons.api?COMMAND=%270%27&format=text&EPHEM_TYPE=VECTORS&STEP_SIZE=%271d%27&START_TIME=%272023-01-25%2000:00%27&STOP_TIME=%272023-01-25%2012:00%27&VEC_TABLE=2&CENTER=%27@0%27
    for(int i=1;i<=solar_size;i++){
      if(i == 9){
        i++;
      }
      data.clear();

      req="https://ssd.jpl.nasa.gov/api/horizons.api?COMMAND=%27";
      req+=std::to_string(i);
      if(i<solar_size){
        req+="99%27&format=text&EPHEM_TYPE=VECTORS&STEP_SIZE=%271d%27&START_TIME=%27"+date+"%2000:00%27&STOP_TIME=%27"+date+"%2012:00%27&VEC_TABLE=2&CENTER=%27@0%27";
      }else{
        req+="%27&format=text&EPHEM_TYPE=VECTORS&STEP_SIZE=%271d%27&START_TIME=%27"+date+"%2000:00%27&STOP_TIME=%27"+date+"%2012:00%27&VEC_TABLE=2&CENTER=%27@0%27";
      }
      
      // std::cerr<<req<<std::endl;
      curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
      res = curl_easy_perform(curl);
      if(res != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      }
      PlanetData planet;
      PlanetPosition position;

      

      parse_web(planet,position,data);

      
      // std::cerr<<planet.mass<<std::endl;
      // std::cerr<<planet.radious<<std::endl;
      if(i == 10){
        planet.mass = 1988500*pow(10,24);
        planet.radious = 695700*1000;
        
      }

      // if(planet.mass == 0){
      //   std::cerr<<data<<std::endl;
      // }
      if(i<solar_size){
        planet.planet_id = i-1;
        position.planet_id = i-1;
      }else{
        planet.planet_id = 8;
        position.planet_id = 8;
      }

      // std::cerr<<(position.positions[0].x)<<std::endl;
      // std::cerr<<(planet.planet_id)<<std::endl;



      data1.push_back(planet);
      data2.push_back(position);

      req.clear();
    }

    curl_easy_cleanup(curl);

  }

  // std::vector<PlanetData> IO::parse_file_json(const std::string& data){
  //   json load = json::parse(data);
  //   std::vector<PlanetData> ret;
  //   ret.resize(load.size());


  //   for(int i=0;i<load.size();i++){
  //     ret[i].mass = load[i]["mass"];
  //     ret[i].radious = load[i]["radious"] ;
  //     ret[i].velocity.x = load[i]["velocity"][0];
  //     ret[i].velocity.y = load[i]["velocity"][1];
  //     ret[i].velocity.z = load[i]["velocity"][2];
  //     ret[i].velocity.x = load[i]["colour"][0];
  //     ret[i].velocity.y = load[i]["colour"][1];
  //     ret[i].velocity.z = load[i]["colour"][2];
  //     ret[i].planet_id = load[i]["planet_id"] ;
  //   }

  //   return ret;

  // }

  std::vector<PlanetData> IO::parse_file(const std::string& data){
    std::vector<PlanetData> ret;
    PlanetData planet;
    planet.deserialize(data);
    ret.push_back(planet);
    return ret;

  }

  // std::string IO::serialize_file_json(const std::vector<PlanetData>& data){
  //   json save;
  //   for(int i=0;i<data.size();i++){
  //     save[i]["mass"] = data[i].mass;
  //     save[i]["radious"] = data[i].radious;
  //     save[i]["velocity"] = {data[i].velocity.x,data[i].velocity.y,data[i].velocity.z};
  //     save[i]["colour"] = {data[i].colour.x,data[i].colour.y,data[i].colour.z};
  //     save[i]["planet_id"] = data[i].planet_id;
  //   }
  //   return save.dump();
  // }

  std::string IO::serialize_file(std::vector<PlanetData>& data){
    return data.at(0).serialize();
  }

 

  std::string IO::read_web(const std::string& path){
    return "";
  }

  void IO::read_file(std::vector<PlanetData>& data1, std::vector<PlanetPosition>& data2, const std::string& filename){
    data1.clear();
    data2.clear();

    std::ifstream file(filename,std::ios::binary);
    if(!file.is_open()){
      throw;
    }
    std::size_t size;
    
    while(1){
      std::string data;
      PlanetData planet;
      PlanetPosition position;
      file.read((char*)(&size),sizeof(size));
      if(file.eof()){
        break;
      }
      data.resize(size);
      file.read(&data[0],size);
      planet = planet.deserialize(data);
      data1.push_back(planet);

      file.read((char*)(&size),sizeof(size));
      data.resize(size);
      file.read(&data[0],size);
      position = position.deserialize(data);
      data2.push_back(position);
    }

    file.close();

  }

  //   std::string IO::read_file(const std::string& path){
  //   std::ifstream file(path);
  //   if(!file.is_open()){
  //     return "";
  //   }

  //   std::string ret;

  //   file.seekg(0, std::ios::end);
  //   size_t length = file.tellg();

  //   ret.resize(length);
  //   file.seekg(0, std::ios::beg);
  //   file.read(&ret[0],length);

  //   file.close();
  //   return ret;
  // }

  bool IO::write_file(const std::string& data, const std::string& path){
    std::ofstream file(path);
    if(!file.is_open()){
      return false;
    }
    file << data;
    file.close();
    return true;
  }
