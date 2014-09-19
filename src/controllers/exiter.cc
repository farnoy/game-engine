#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include "controllers/exiter.hh"
#include "renderer.hh"
#include "runner.hh"

using namespace engine::controllers;

exiter::exiter() : controller{"exiter", {sf::Event::Closed, sf::Event::KeyPressed}} {}

bool exiter::handle(const sf::Event& event, runner& runner) {
  if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Key::Escape) {
    runner.get_renderer().get_window()->close();
    return false;  // stop propagating
  } else
    return controller::handle(event, runner);  // continue propagating
}
