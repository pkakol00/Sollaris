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
  
  // CREATE_EVENT(read, std::vector<PlanetData>, const std::string&);
  // CREATE_EVENT(write, void, std::vector<PlanetData>, const std::string&)
  public:
    void write_event(std::vector<PlanetData> data1, std::vector<PlanetPosition> data2, const std::string& filename);
    void read_event(std::vector<PlanetData>& data1, std::vector<PlanetPosition>& data2, const std::string& filename);

    void get_web(std::vector<PlanetData>& data1, std::vector<PlanetPosition>& data2, std::string date = "");
    void parse_web(PlanetData &planet, PlanetPosition& position, const std::string& data);

  private:
    std::vector<PlanetData> parse_file(const std::string& data);
    std::string serialize_file(std::vector<PlanetData>& data);

    std::string read_web(const std::string& path);
    // std::string read_file(const std::string& path);
    void read_file(std::vector<PlanetData>& data1, std::vector<PlanetPosition>& data2, const std::string& filename);
    bool write_file(const std::string& path, const std::string& data);

};

#endif // __IO_H__