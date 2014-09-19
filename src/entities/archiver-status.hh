#pragma once
#include <memory>
#include "entity.hh"

namespace sf {
class RectangleShape;
class RenderTarget;
}
namespace engine {
class archiver;
class runner;
namespace entities {
struct archiver_status : public entity {
  std::unique_ptr<sf::RectangleShape> _bar;

  archiver const& _archiver;

  archiver_status(runner& runner);

  virtual void draw(sf::RenderTarget& target) override;

  virtual void update(scheduling::ticks_count ticks) override;

  virtual entity* copy() const override;
};
}
}
