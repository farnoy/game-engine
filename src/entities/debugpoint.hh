#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "entity.hh"

namespace sf {
class RenderTarget;
}

namespace engine {
namespace scheduling {
using ticks_count = unsigned short;
}
namespace entities {

struct debug_point : public entity {
  static const short radius = 8;

  sf::CircleShape shape;

  debug_point(const sf::Vector2f& location);

  virtual void draw(sf::RenderTarget& target) override;

  virtual void update(scheduling::ticks_count ticks) override;
};
}
}
