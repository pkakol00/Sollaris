#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "Log.h"
#include <functional>

#define CREATE_EVENT(_name, _return, ...) \
  public: \
  std::function<_return(__VA_ARGS__)> _name##_event_function; \
  void subscribe_to_##_name(std::function<_return( __VA_ARGS__ )> f) { \
    LOG("Subscribing to" + std::string(#_name));\
    _name##_event_function = f; \
  } \

#endif // __EVENTS_H__