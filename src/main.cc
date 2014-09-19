#include <iostream>
// FIXME
#include <SFML/Graphics/RectangleShape.hpp>
#include <thread>
#include <glog/logging.h>
#include "runner.hh"
#include "entity-manager.hh"
#include "renderer.hh"
#include "controller-manager.hh"
#include "controllers/exiter.hh"
#include "controllers/actor-spawner.hh"
#include "controllers/coord-debugger.hh"
#include "controllers/pauser.hh"
#include "controllers/player.hh"
#include "controllers/viewport-zoomer.hh"
#include "controllers/physics.hh"
#include "controllers/hud.hh"
#include "controllers/rewinder.hh"
#include "entities/background-image.hh"
#include "entities/archiver-status.hh"

int main(int /* argc */, char** argv) {
  google::InitGoogleLogging(argv[0]);

  engine::runner runner;
  runner.attach_controller<engine::controllers::exiter>();
  runner.attach_controller<engine::controllers::coordinate_debugger>();
  runner.attach_controller<engine::controllers::actor_spawner>();
  runner.attach_controller<engine::controllers::pauser>();
  runner.attach_controller<engine::controllers::player>();
  runner.attach_controller<engine::controllers::rewinder>();
  runner.attach_controller<engine::controllers::viewport_zoomer>();
  runner.attach_controller<engine::controllers::physics>();
  auto tag =
      runner.get_entity_manager().add(std::make_shared<engine::entities::background_image>());
  runner.get_renderer().get_layer("Background").add(tag);

  auto archiver_status = std::make_shared<engine::entities::archiver_status>(runner);
  tag = runner.get_entity_manager().add(archiver_status);
  runner.get_renderer().get_layer("Overlay").add(tag);

  auto hud = std::make_shared<engine::controllers::hud>();
  hud->handle(engine::controllers::hud::positioning::bottom,
              static_cast<sf::Transformable*>(archiver_status->_bar.get()));
  runner.attach_controller(hud);

  runner.run();

  google::ShutdownGoogleLogging();

  return 0;
}
