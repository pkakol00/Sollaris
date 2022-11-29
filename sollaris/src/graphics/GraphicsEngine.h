#ifndef __GRAPHICSENGINE_H__
#define __GRAPHICSENGINE_H__

#include <functional>
#include "../util/common.h"
#include "../util/Log.h"
#include "../util/events.h"

#include <SFML/Window.hpp>
#include <memory>
#include "Shader.h"

#include <util/common.h>
#include <graphics/drawable/Planet.h>
class GraphicsEngine {
  CREATE_EVENT(planet_addition, void, int);
  CREATE_EVENT(planet_removeal, void, int);
  CREATE_EVENT(radious_change, void, int, double);
  CREATE_EVENT(mass_change, void, int, double);
  CREATE_EVENT(position_change, void, int, Vec3);
  CREATE_EVENT(velocity_change, void, int, double);
  CREATE_EVENT(interval_change, void, double);
  CREATE_EVENT(G_change, void, int, double);

public:
  GraphicsEngine();

  bool display();
  void setPlanetPositions(std::shared_ptr<std::vector<PlanetPosition>>);
private:
  std::shared_ptr<sf::Window> window_ptr;
  ge::Shader shader;

  std::shared_ptr<std::vector<PlanetPosition>> planet_positions;
  std::vector<Planet> planets_drawables;

  bool pollEvents();
  void init();
};
#endif // __GRAPHICSENGINE_H__