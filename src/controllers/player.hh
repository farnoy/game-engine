#pragma once
#include <memory>
#include "controller.hh"

namespace engine {
namespace entities {
class character;
}
namespace controllers {
class player : public controller {
  std::weak_ptr<entities::character> _character;

 public:
  player();

  virtual bool handle(const sf::Event& event, runner& runner) override;
};
}
}
