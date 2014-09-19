#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "renderer.hh"
#include "entity-manager.hh"
#include "entity.hh"
#include "identification/tag.hh"

using namespace engine;

renderer::renderer()
    : _window(std::make_shared<sf::RenderWindow>(sf::VideoMode{800, 600}, "game-engine")) {
  this->_render_layers.emplace_back(new render_layer(*this, "Background"));
  this->_render_layers.emplace_back(new render_layer(*this, "Foreground"));
  this->_render_layers.emplace_back(new render_layer(*this, "Overlay"));
}

void renderer::render(entity_manager& manager) {
  this->_window->clear(sf::Color{100, 149, 237, 255});

  auto view = this->_window->getView();

  for (auto& layer : this->_render_layers) {
    this->_window->setView(layer->_view);

    for (identification::tag entity_tag : layer->_entities) {
      auto entity = manager.get_entity_by_tag(entity_tag).lock();
      if (entity)
        entity->draw(*this->_window);
    }

    this->_window->setView(view);
  }

  this->_window->display();
}

bool renderer::is_window_open() const { return _window->isOpen(); }

std::shared_ptr<sf::RenderWindow> renderer::get_window() {
  return {_window};
}

render_layer& renderer::get_layer(std::string const& name) noexcept(false) {
  auto found_it = std::find_if(
      this->_render_layers.begin(),
      this->_render_layers.end(),
      [&](std::unique_ptr<render_layer> & layer)->bool { return layer->_name == name; });

  if (found_it != this->_render_layers.end()) {
    return **found_it;
  }

  throw(std::logic_error("Layer with given name does not exist: " + name));
}
