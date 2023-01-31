#include "serializable.capnp.h"
#include "common.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <cstring>
#include <string>
#include <iostream>

//capnp compile -oc++ serializable.capnp
//g++ -o serializable serializable.cpp serializable.capnp.c++ `pkg-config --cflags --libs capnp`
//./serializable

PlanetPosition::~PlanetPosition() {};

PlanetPosition::PlanetPosition() {};

PlanetPosition::PlanetPosition(std::deque<Vec3> positions, int planet_id) : positions(positions), planet_id(planet_id) {}

PlanetData::PlanetData() {};

PlanetData::~PlanetData() {};

PlanetData::PlanetData(double mass, double radious, Vec3 velocity, Vec3 colour, int planet_id) :
    mass(mass), radious(radious), velocity(velocity), colour(colour), planet_id(planet_id) {}


std::string PlanetData::serialize(){
    ::capnp::MallocMessageBuilder message_builder;
    PlData::Builder message = message_builder.initRoot<PlData>();

    message.setMass( this->mass );
    message.setRadious( this->radious );
    message.setPlanetId( this->planet_id );
    message.setV1( this->velocity.x );
    message.setV2( this->velocity.y );
    message.setV3( this->velocity.z );
    message.setColourX( this->colour.x );
    message.setColourY( this->colour.y );
    message.setColourZ( this->colour.z );

    auto encoded_array = capnp::messageToFlatArray(message_builder);
    auto encoded_array_ptr = encoded_array.asChars();
    auto encoded_char_array = encoded_array_ptr.begin();
    auto size = encoded_array_ptr.size();

    auto bytes = encoded_array.asBytes();
    std::string data(bytes.begin(), bytes.end());
    std::string toReturn = std::string(data);
    return toReturn;
}

PlanetData PlanetData::deserialize(const std::string& data){
    PlData::Reader objRestore;

    if(reinterpret_cast<uintptr_t>(data.data()) % sizeof(void*) == 0) {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(data))),
            reinterpret_cast<const capnp::word*>(&(*std::end(data))));
        capnp::FlatArrayMessageReader message2(view);
        objRestore = message2.getRoot<PlData>();
    }
    else {
        size_t numWords = data.size() / sizeof(capnp::word);

        if(data.size() % sizeof(capnp::word) != 0) {
            numWords++;
        }

        capnp::word dataWords[numWords];
        std::memcpy(dataWords, data.data(), data.size());
        kj::ArrayPtr<capnp::word> dataWordsPtr(dataWords, dataWords + numWords);
        capnp::FlatArrayMessageReader message2(dataWordsPtr);
        objRestore = message2.getRoot<PlData>();
    }
    return PlanetData(objRestore.getMass(), objRestore.getRadious(), 
        Vec3(objRestore.getV1(), objRestore.getV2(), objRestore.getV3()),
        Vec3(objRestore.getColourX(), objRestore.getColourY(), objRestore.getColourZ()), objRestore.getPlanetId());
}


std::string PlanetPosition::serialize(){
    ::capnp::MallocMessageBuilder message_builder;
    PlPosition::Builder message = message_builder.initRoot<PlPosition>();

    message.setPlanetId( this->planet_id );
    int s = this->positions.size();
    ::capnp::List<Vector>::Builder positions = message.initPositions(s);
    for (int i = 0; i < s; i++){
        Vector::Builder vector = positions[i];
        Vec3 vec = this->positions.front();
        this->positions.pop_front();
        vector.setX(vec.x);
        vector.setY(vec.y);
        vector.setZ(vec.z);
    }
    auto encoded_array = capnp::messageToFlatArray(message_builder);
    auto encoded_array_ptr = encoded_array.asChars();
    auto encoded_char_array = encoded_array_ptr.begin();
    auto size = encoded_array_ptr.size();

    auto bytes = encoded_array.asBytes();
    std::string data(bytes.begin(), bytes.end());
    std::string toReturn = std::string(data);
    return toReturn;
}


PlanetPosition PlanetPosition::deserialize(const std::string& data){
    PlPosition::Reader objRestore;

    if(reinterpret_cast<uintptr_t>(data.data()) % sizeof(void*) == 0) {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(data))),
            reinterpret_cast<const capnp::word*>(&(*std::end(data))));
        capnp::FlatArrayMessageReader message2(view);
        objRestore = message2.getRoot<PlPosition>();
    }
    else {
        size_t numWords = data.size() / sizeof(capnp::word);

        if(data.size() % sizeof(capnp::word) != 0) {
            numWords++;
        }

        capnp::word dataWords[numWords];
        std::memcpy(dataWords, data.data(), data.size());
        kj::ArrayPtr<capnp::word> dataWordsPtr(dataWords, dataWords + numWords);
        capnp::FlatArrayMessageReader message2(dataWordsPtr);
        objRestore = message2.getRoot<PlPosition>();
    }
    std::deque<Vec3> vector;
    for(Vector::Reader v : objRestore.getPositions()) {
        vector.push_back(Vec3(v.getX(), v.getY(), v.getZ()));
    }
    return PlanetPosition(vector, objRestore.getPlanetId());
}
