#pragma once
#include <SFML/Window/Event.hpp>
#include "controller.hh"

namespace engine {
class runner;
}

namespace engine {
namespace controllers {
class pauser : public controller {
 public:
  pauser();

  virtual bool handle(const sf::Event& event, runner& runner) override;
};
}
}
