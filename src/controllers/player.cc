#include "controllers/player.hh"
#include "utility/angles.hh"
#include <SFML/Window/Event.hpp>
#include <glog/logging.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "entity-manager.hh"
#include "entities/character.hh"
#include "runner.hh"
#include "renderer.hh"

using namespace engine::controllers;
using engine::utility::direction;

player::player() : controller{"player", {sf::Event::Count, sf::Event::MouseMoved}} {}

bool player::handle(const sf::Event& event, runner& runner) {
  auto& em = runner.get_entity_manager();
  auto character = this->_character.lock();

  if (!character) {
    character = std::make_shared<entities::character>();

    auto tag = em.add(character);
    runner.get_renderer().get_layer("Foreground").add(tag);

    this->_character = {character};
  }

  auto& view = runner.get_renderer().get_layer("Foreground").get_view();

  auto mouse_world = runner.get_renderer().get_window()->mapPixelToCoords(
      sf::Mouse::getPosition(*runner.get_renderer().get_window()), view);

  auto middle = character->get_position() + mouse_world;
  middle /= 2.f;
  view.setCenter(middle);

  // rotate the character entity
  auto v = mouse_world - character->get_position();
  character->set_rotation(v);

  if (event.type == sf::Event::Count) {
#define CHECK_PRESSED(key) sf::Keyboard::isKeyPressed(sf::Keyboard::key)
    if (CHECK_PRESSED(W))
      character->move_intent(direction::north);
    if (CHECK_PRESSED(A))
      character->move_intent(direction::west);
    if (CHECK_PRESSED(S))
      character->move_intent(direction::south);
    if (CHECK_PRESSED(D))
      character->move_intent(direction::east);
  }
  return controller::handle(event, runner);
}
