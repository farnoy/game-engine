#pragma once
#include <SFML/System/Vector2.hpp>
#include <utility>

namespace engine {
namespace utility {
namespace angles {
enum class type {
  degree,
  radian
};

template <type T>
class angle {
  float _angle;

 public:
  angle(float angle);

  angle(angle&& other);

  angle(angle const& other);

  angle(sf::Vector2f const& v);

  template <type Y>
  angle<Y> as() const;

  float get() const;

  angle operator+(float value) const;

  angle operator-(float value) const;

  float get_transformable_rotation() const;
};

#ifndef SPECIALIZE
extern template class angle<type::degree>;
extern template class angle<type::radian>;
#endif
}
}
}
