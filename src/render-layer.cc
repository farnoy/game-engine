#include "renderer.hh"
#include "render-layer.hh"
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <stdexcept>

using engine::render_layer;
using engine::renderer;

render_layer::render_layer(renderer& renderer, std::string name)
    : _renderer(renderer), _name(name) {
  auto size = renderer.get_window()->getSize();
  _view.reset({0, 0, static_cast<float>(size.x), static_cast<float>(size.y)});
}

sf::View& render_layer::get_view() { return this->_view; }

void render_layer::add(identification::tag tag) { this->_entities.insert(tag); }
