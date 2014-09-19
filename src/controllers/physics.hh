#pragma once
#include <SFML/Window/Event.hpp>
#include "controller.hh"
#include <Box2D/Box2D.h>

namespace engine {
class runner;
}

namespace engine {
namespace controllers {
struct physics : public controller {
  b2World world;

  physics();

  virtual bool handle(const sf::Event& event, runner& runner) override;
};
}
}
