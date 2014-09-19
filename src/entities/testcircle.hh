#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <memory>
#include "entity.hh"
#include "utility/angles.hh"

using engine::utility::angles::type;
using engine::utility::angles::angle;

class b2Body;

namespace sf {
class CircleShape;
class RenderTarget;
}
namespace engine {
namespace scheduling {
using ticks_count = unsigned short;
}
namespace controllers {
struct physics;
}

namespace entities {
struct testcircle : public entity {
  std::unique_ptr<sf::CircleShape> shape;
  angle<type::radian> _angle;
  controllers::physics& physics;
  b2Body* body;

  testcircle(controllers::physics&, const sf::Vector2f& origin, angle<type::radian> _angle);

  testcircle(const testcircle& other);

  virtual void draw(sf::RenderTarget& target) override;

  virtual void update(scheduling::ticks_count ticks) override;

  virtual entity* copy() const override;
};
}
}
