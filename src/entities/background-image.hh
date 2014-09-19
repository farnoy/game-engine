#pragma once
#include "entity.hh"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace engine {
namespace entities {

class background_image : public entity {
  sf::Texture _texture;
  sf::Sprite _sprite;

 public:
  background_image();

  virtual void draw(sf::RenderTarget& target) override;

  virtual void update(scheduling::ticks_count ticks) override;

  virtual entity* copy() const;
};
}
}
