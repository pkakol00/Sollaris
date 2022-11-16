#include "graphics/GraphicsEngine.h"
#include "physics/PhysicsEngine.h"
#include "io/IO.h"

void foo(int a, double b) {
  std::cout << a << b << std::endl;
}

int main()
{
  GraphicsEngine ge;
  ge.subscribe_to_radious_change(&foo);
  LOG("foo");
  ge.radious_change_event_function(12, .2);
}