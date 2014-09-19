#pragma once
#include <SFML/Window/Event.hpp>
#include "controller.hh"
#include "scheduling.hh"

namespace engine {
class runner;
}

namespace engine {

namespace controllers {
class actor_spawner : public controller {
  engine::scheduling::tick_duration _charging_timer;

 public:
  actor_spawner();

  virtual bool handle(const sf::Event&, runner&) override;
};
}
}
