#include "frame.hh"
#include "runner.hh"
#include "controllers/physics.hh"
#include <glog/logging.h>

using namespace engine;

frame::frame(const runner& _runner) : _entity_manager(_runner.get_entity_manager()) {
  if (auto physics = _runner.get_controller_manager().get_by_type("physics").lock()) {
    auto& world = std::static_pointer_cast<controllers::physics const>(physics)->world;

    auto body = world.GetBodyList();
    int i = 0;
    while (body) {
      i++;
      auto transform = body->GetTransform();
      auto velocity = body->GetLinearVelocity();
      this->_world_snapshot.emplace(std::make_pair(
          body,
          rigid_body_data{transform.p.x, transform.p.y, transform.q, {velocity.x, velocity.y}}));
      body = body->GetNext();
    }
  }
}

void frame::replay(runner& _runner) {
  std::swap(_runner.get_entity_manager(), _entity_manager);

  if (_runner.get_controller_manager().has("physics")) {
    auto& world = std::static_pointer_cast<controllers::physics>(
        _runner.get_controller_manager().get_by_type("physics").lock())->world;
    auto body = world.GetBodyList();
    while (body) {
      auto iter = this->_world_snapshot.find(body);
      if (iter != this->_world_snapshot.end()) {
        auto& rigid_data = std::get<1>(*iter);
        auto position = b2Vec2{rigid_data.x, rigid_data.y};
        auto angle = rigid_data.rotation.GetAngle();
        body->SetTransform(position, angle);
        body->SetLinearVelocity(rigid_data.linear_velocity);
      }
      body = body->GetNext();
    }
  }
}

const entity_manager& frame::get_entity_manager() const { return _entity_manager; }
