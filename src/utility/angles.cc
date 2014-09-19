#define SPECIALIZE
#include "utility/angles.hh"
#include <cmath>

namespace engine {
namespace utility {
namespace angles {

template <>
template <>
angle<type::degree> angle<type::radian>::as<type::degree>() const {
  return angle<type::degree>(_angle * 180.f / static_cast<float>(M_PI));
}

template <>
template <>
angle<type::radian> angle<type::degree>::as<type::radian>() const {
  return angle<type::radian>(_angle * static_cast<float>(M_PI) / 180.f);
}

template <>
angle<type::radian>::angle(const sf::Vector2f& vector)
    : angle(std::atan2(vector.y, vector.x)) {}

template <>
angle<type::degree>::angle(const sf::Vector2f& vector)
    : angle(angle<type::radian>(std::atan2(vector.y, vector.x)).as<type::degree>()) {}

template <type T>
float angle<T>::get() const {
  return _angle;
}

template <type T>
angle<T> angle<T>::operator+(float value) const {
  return angle<T>(_angle + value);
}

template <type T>
angle<T> angle<T>::operator-(float value) const {
  return angle<T>(_angle - value);
}

template <>
float angle<type::degree>::get_transformable_rotation() const {
  return (*this + 90.f).get();
}

template <>
float angle<type::radian>::get_transformable_rotation() const {
  return this->as<type::degree>().get_transformable_rotation();
}

template <type T>
angle<T>::angle(float angle)
    : _angle(angle) {}

template <type T>
angle<T>::angle(angle&& other)
    : _angle(std::move(other._angle)) {}

template <type T>
angle<T>::angle(angle const& other)
    : _angle(other._angle) {}

template class angle<type::degree>;
template class angle<type::radian>;
}
}
}
