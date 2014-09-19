#pragma once
#include <SFML/Window/Event.hpp>
#include "controller.hh"

namespace engine {
class runner;

namespace controllers {

class exiter : public controller {
 public:
  exiter();

  virtual bool handle(const sf::Event& event, runner& runner) override;
};
}
}
