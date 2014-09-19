#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <glog/logging.h>
// #include "resources.h"
#include "entities/character.hh"

using namespace engine::entities;

character::character() : _body_texture(new sf::Texture) {
  //LOG_IF(FATAL, !_body_texture->loadFromFile(CHARACTER_IMAGE_PATH))
  //    << "Loading character image failed";
  this->_body.setOrigin(30, 30);
  //this->_body.setTexture(_body_texture.get());
}

void character::draw(sf::RenderTarget& target) { target.draw(_body); }

void character::update(scheduling::ticks_count ticks) {
  this->_body.setPosition(this->_body.getPosition() +
                          (sf::Vector2f{this->_move_intent.construct_offset()} *
                           static_cast<float>(character::speed * ticks)));
}

void character::move_intent(utility::direction direction) noexcept { _move_intent.add(direction); }

sf::Vector2f const& character::get_position() const { return this->_body.getPosition(); }

void character::set_rotation(angle<type::degree> _angle) {
  this->_body.setRotation(_angle.get_transformable_rotation());
}

engine::entity* character::copy() const {
  return static_cast<engine::entity*>(const_cast<character*>(this));
}
