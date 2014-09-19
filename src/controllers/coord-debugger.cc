#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "controllers/coord-debugger.hh"
#include "entities/debugpoint.hh"
#include "entity-manager.hh"
#include "runner.hh"
#include "renderer.hh"

using namespace engine::controllers;

coordinate_debugger::coordinate_debugger()
    : controller{"coordinate-debugger",
                 {sf::Event::MouseButtonPressed, sf::Event::MouseButtonReleased,
                  sf::Event::Count /* bullet time when doing shit */}} {}

bool coordinate_debugger::handle(const sf::Event& event, runner& runner) {
  if (event.type == sf::Event::Count && this->_point) {
    _point->shape.setPosition(runner.get_renderer().get_window()->mapPixelToCoords(
        sf::Mouse::getPosition(*runner.get_renderer().get_window()),
        runner.get_renderer().get_layer("Overlay").get_view()));
  } else if (event.mouseButton.button == sf::Mouse::Button::Left) {
    if (event.type == sf::Event::MouseButtonPressed) {
      _point = std::make_shared<entities::debug_point>(
          runner.get_renderer().get_window()->mapPixelToCoords(
              sf::Mouse::getPosition(*runner.get_renderer().get_window()),
              runner.get_renderer().get_layer("Overlay").get_view()));
      auto tag = runner.get_entity_manager().add(_point);
      runner.get_renderer().get_layer("Overlay").add(tag);
    } else {  // mouse button released
      runner.get_entity_manager().remove(_point);
      _point.reset();
    }
  }

  return true;
}
