#pragma once
#include <SFML/Window/Event.hpp>
#include <memory>
#include "controller.hh"

namespace engine {
class runner;
namespace entities {
struct debug_point;
}

namespace controllers {

class coordinate_debugger : public controller {
  std::shared_ptr<entities::debug_point> _point;

 public:
  coordinate_debugger();

  virtual bool handle(const sf::Event& event, runner& runner) override;
};
}
}
