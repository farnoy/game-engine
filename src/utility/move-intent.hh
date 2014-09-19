#pragma once
#include "utility/direction.hh"
#include <bitset>
#include <SFML/System/Vector2.hpp>

namespace engine {
namespace utility {

class move_intent {
  std::bitset<9> _bits;

 public:
  void add(direction dir);

  void remove(direction dir);

  bool check(direction dir) const;

  sf::Vector2i construct_offset();
};
}
}
