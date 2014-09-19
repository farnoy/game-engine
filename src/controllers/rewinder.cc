#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "controllers/rewinder.hh"
#include "runner.hh"
#include "scheduler.hh"

using namespace engine::controllers;

rewinder::rewinder() : controller("rewinder", {sf::Event::KeyPressed}) {}

bool rewinder::handle(const sf::Event& event, runner& runner) {
  if (event.key.code == sf::Keyboard::R) {
    runner.get_scheduler().toggle_reverse();
    return false;
  } else
    return controller::handle(event, runner);
}
