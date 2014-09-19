#pragma once
#include <memory>
#include <vector>
#include "identification/tag.hh"
#include "render-layer.hh"
#include <stdexcept>

namespace sf {
class RenderWindow;
}  // namespace sf

namespace engine {
class entity_manager;

class renderer {
  friend class runner;
  std::shared_ptr<sf::RenderWindow> _window;
  std::vector<std::unique_ptr<render_layer> > _render_layers;

 public:
  renderer();

  renderer(const renderer&) = delete;

  renderer(renderer&&) = default;

  renderer& operator=(const renderer&) = delete;

  renderer& operator=(renderer&&) = default;

  void render(entity_manager& manager);

  render_layer& get_layer(std::string const& name) noexcept(false);

  bool is_window_open() const;

  std::shared_ptr<sf::RenderWindow> get_window();
};
}
