#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "entities/debugpoint.hh"

using namespace engine::entities;

debug_point::debug_point(const sf::Vector2f& location)
    : shape(sf::CircleShape(debug_point::radius)) {
  shape.setPosition(location);
  shape.setOrigin(debug_point::radius, debug_point::radius);
  shape.setFillColor(sf::Color::Red);
}

void debug_point::draw(sf::RenderTarget& target) { target.draw(this->shape); }

void debug_point::update(scheduling::ticks_count) {}
