#include <SFML/Graphics/RenderTarget.hpp>
#include <glog/logging.h>
#include "entities/background-image.hh"
//#include "resources.h"

using engine::entity;
using engine::entities::background_image;

background_image::background_image() {
  // LOG_IF(FATAL, !_texture.loadFromFile(BACKGROUND_IMAGE_PATH)) << "Loading background image failed";

  _texture.setSmooth(true);

  // _sprite.setTexture(_texture, true);

  // auto size = _texture.getSize();
  // not needed since the Background layer was introduced
  // auto half_size = sf::Vector2f { size / 2u }
  //;
  //_sprite.setOrigin(half_size);
}

void background_image::draw(sf::RenderTarget& target) { target.draw(_sprite); }

void background_image::update(scheduling::ticks_count) {}

entity* background_image::copy() const {
  auto cv_lifted = const_cast<background_image*>(this);
  return static_cast<entity*>(cv_lifted);
}
