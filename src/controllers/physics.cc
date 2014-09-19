#include <SFML/Window/Keyboard.hpp>
#include "controllers/physics.hh"
#include <glog/logging.h>
#include "runner.hh"
#include "scheduler.hh"
#include "scheduling.hh"

using namespace engine::controllers;

physics::physics() : controller{"physics", {sf::Event::Count}}, world(b2Vec2{0.f, 0.f}) {}

bool physics::handle(const sf::Event& event, runner& runner) {
  if (!runner.get_scheduler().is_stopped()) {
    const auto timestep = static_cast<float>(engine::scheduling::tick_duration(1).count()) *
                          engine::scheduling::update_frequency::num /
                          engine::scheduling::update_frequency::den;
    this->world.Step(timestep, 8, 3);
  }
  return controller::handle(event, runner);
}
