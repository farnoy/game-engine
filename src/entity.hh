#pragma once
#include <memory>
#include "identification/tag.hh"

namespace sf {
class RenderTarget;
}

namespace engine {
class entity_manager;
namespace scheduling {
using ticks_count = unsigned short;
}

class entity {
  friend class entity_manager;
  identification::tag _tag;

 public:
  virtual ~entity();

  virtual void draw(sf::RenderTarget& target) = 0;

  virtual void update(scheduling::ticks_count ticks) = 0;

  identification::tag const& get_tag() const;

  bool is_registered() const;

  virtual entity* copy() const;
};
}
