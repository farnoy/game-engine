#include <glog/logging.h>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "controllers/actor-spawner.hh"
#include "controllers/physics.hh"
#include "entities/testcircle.hh"
#include "entity-manager.hh"
#include "entities/character.hh"
#include "runner.hh"
#include "renderer.hh"
#include "utility/angles.hh"
#include <Box2D/Box2D.h>

using namespace engine::controllers;

actor_spawner::actor_spawner()
    : controller(
          "actor-spawner",
          {sf::Event::MouseButtonPressed, sf::Event::MouseButtonReleased, sf::Event::Count}) {}

bool actor_spawner::handle(const sf::Event& event, runner& runner) {
  if (event.type == sf::Event::MouseButtonPressed) {
    this->_charging_timer = this->_charging_timer.zero();
  } else if (event.type == sf::Event::Count) {
    this->_charging_timer += engine::scheduling::tick_duration(1);
  } else if (event.mouseButton.button == sf::Mouse::Button::Middle) {
    auto window = runner.get_renderer().get_window();
    auto mouse_world =
        window->mapPixelToCoords(sf::Mouse::getPosition(*runner.get_renderer().get_window()));
    auto view_center = window->getView().getCenter();

    if (!runner.get_controller_manager().has("physics")) {
      DLOG(WARNING) << "Cannot find physics";
      return true;
    }

    auto physics = std::static_pointer_cast<engine::controllers::physics>(
        runner.get_controller_manager().get_by_type("physics").lock());

    // find character entity
    auto character_pred = [&](
        std::pair<const engine::identification::tag, std::shared_ptr<engine::entity> > pair)->bool {
      return static_cast<bool>(
          std::dynamic_pointer_cast<engine::entities::character>(std::get<1>(pair)));
    };
    auto& em = runner.get_entity_manager();
    auto character_it = std::find_if(em.begin(), em.end(), character_pred);
    auto character =
        std::static_pointer_cast<engine::entities::character>(std::get<1>(*character_it));

    using engine::utility::angles::type;
    using engine::utility::angles::angle;
    auto force_angle = engine::utility::angles::angle<type::radian>(mouse_world - view_center);
    auto testcircle =
        std::make_shared<entities::testcircle>(*physics, character->get_position(), force_angle);
    // initial push
    auto initial = b2Vec2{std::cos(force_angle.get()), std::sin(force_angle.get())};
    initial *= this->_charging_timer.count() * 10;
    testcircle->body->ApplyForceToCenter(initial, true);

    auto tag = runner.get_entity_manager().add(testcircle);
    runner.get_renderer().get_layer("Foreground").add(tag);

    return false;  // stop propagating
  }
  return controller::handle(event, runner);  // continue propagating
}
