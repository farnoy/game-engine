#pragma once
#include "entity-manager.hh"
#include <Box2D/Box2D.h>
#include <unordered_map>

namespace engine {
struct rigid_body_data {
  float32 x, y;
  b2Rot rotation;
  b2Vec2 linear_velocity;
};
class runner;
class frame {
  // any metadata that is required
  entity_manager _entity_manager;
  std::unordered_map<b2Body const*, rigid_body_data> _world_snapshot;

 public:
  frame(const runner&);

  void replay(runner&);

  const entity_manager& get_entity_manager() const;
};
}
