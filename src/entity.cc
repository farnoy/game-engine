#include "entity.hh"

namespace engine {
namespace identification {
struct tag;
}
}

using namespace engine;

// entity::entity() {}

entity::~entity() {}

identification::tag const& entity::get_tag() const { return this->_tag; }

bool entity::is_registered() const { return !this->_tag.is_empty(); }

entity* entity::copy() const { return nullptr; }
