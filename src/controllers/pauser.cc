#include <SFML/Window/Keyboard.hpp>
#include "controllers/pauser.hh"
#include "runner.hh"
#include "scheduler.hh"

using namespace engine::controllers;

pauser::pauser() : controller{"pauser", {sf::Event::KeyPressed}} {}

bool pauser::handle(const sf::Event& event, runner& runner) {
  if (event.key.code == sf::Keyboard::Pause) {
    auto& sched = runner.get_scheduler();
    if (sched.is_stopped()) {
      sched.start();
    } else
      sched.stop();

    return false;  // stop propagating
  } else
    return controller::handle(event, runner);
}
