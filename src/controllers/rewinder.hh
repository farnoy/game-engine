#pragma once
#include "controller.hh"

namespace engine {
class runner;
}

namespace engine {
namespace controllers {
class rewinder : public controller {
 public:
  rewinder();

  virtual bool handle(const sf::Event& event, runner& runner) override;
};
}
}
