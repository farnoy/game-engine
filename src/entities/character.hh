#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "entity.hh"
#include "scheduling.hh"
#include "utility/move-intent.hh"
#include "utility/angles.hh"

using engine::utility::angles::angle;
using engine::utility::angles::type;

namespace sf {
class RenderTarget;
class Texture;
}

namespace engine {
namespace entities {

class character : public entity {
  sf::CircleShape _body{30};
  std::shared_ptr<sf::Texture> _body_texture;
  utility::move_intent _move_intent;

 public:
  character();

  static constexpr const unsigned short speed = 5;

  virtual void draw(sf::RenderTarget& target) override;

  virtual void update(scheduling::ticks_count ticks) override;

  sf::Vector2f const& get_position() const;

  void set_rotation(angle<type::degree> angle);

  virtual entity* copy() const override;

  void move_intent(utility::direction direction) noexcept;
};
}
}
