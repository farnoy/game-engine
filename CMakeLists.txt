cmake_minimum_required(VERSION 3.0)

find_package(SFML 2 REQUIRED system window graphics)

add_executable(game-engine
  src/main.cc

  src/archiver.cc
  src/controller-manager.cc
  src/controller.cc
  src/entity-manager.cc
  src/entity.cc
  src/frame.cc
  src/render-layer.cc
  src/renderer.cc
  src/runner.cc
  src/scheduler.cc
  src/scheduling.cc

  src/controllers/actor-spawner.cc
  src/controllers/coord-debugger.cc
  src/controllers/exiter.cc
  src/controllers/hud.cc
  src/controllers/pauser.cc
  src/controllers/physics.cc
  src/controllers/player.cc
  src/controllers/rewinder.cc
  src/controllers/viewport-zoomer.cc

  src/entities/archiver-status.cc
  src/entities/background-image.cc
  src/entities/character.cc
  src/entities/debugpoint.cc
  src/entities/testcircle.cc

  src/identification/provider.cc
  src/identification/tag.cc

  src/utility/angles.cc
  src/utility/direction.cc
  src/utility/move-intent.cc
)

set_property(TARGET game-engine PROPERTY COMPILE_FLAGS "${game_engine_COMPILE_FLAGS} --std=c++14")
set_property(TARGET game-engine PROPERTY INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(game-engine sfml-graphics sfml-system sfml-window Box2D glog)
