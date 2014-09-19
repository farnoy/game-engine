#include "utility/move-intent.hh"
#include <SFML/System/Vector2.hpp>

using engine::utility::direction;
using engine::utility::move_intent;
using direction_type = std::underlying_type<direction>::type;

void move_intent::add(direction dir) {
  if (!_bits.test(direction_type(dir)))
    _bits.set(direction_type(dir), true);
}

bool move_intent::check(direction dir) const { return _bits[dir]; }

sf::Vector2i move_intent::construct_offset() {
  sf::Vector2i v;
  if (this->check(direction::north))
    v.y = -1;
  if (this->check(direction::east))
    v.x = 1;
  if (this->check(direction::south)) {
    if (v.y != 0)
      v.y = 0;
    else
      v.y = 1;
  }
  if (this->check(direction::west)) {
    if (v.x != 0)
      v.x = 0;
    else
      v.x = -1;
  }
  _bits.reset();

  return v;
}
