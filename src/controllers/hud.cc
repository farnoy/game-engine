#include <glog/logging.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "runner.hh"
#include "renderer.hh"
#include "controllers/hud.hh"

using engine::controllers::hud;
using engine::runner;

hud::hud() : controller{"hud", {sf::Event::Count}} {}

bool hud::handle(const sf::Event& /* event */, runner& runner) {
  auto window = runner.get_renderer().get_window();
  auto& view = runner.get_renderer().get_layer("Overlay").get_view();

  for (auto element : this->_elements) {
    auto positioning = std::get<0>(element);
    auto transformables = std::get<1>(element);

    if (positioning == hud::positioning::bottom) {
      auto center = view.getCenter();
      auto dimensions = view.getSize();

      sf::Vector2f position{center.x, center.y + dimensions.y / 2 -
                                          (transformables.size() + 1) * hud::element_spacing};
      for (auto transformable : transformables) {
        transformable->setPosition(position);
        position += {0.f, hud::element_spacing};
      }
    }
  }
  return true;
}

void hud::handle(positioning pos, sf::Transformable* trans) {
  this->_elements[pos].push_back(trans);
}
