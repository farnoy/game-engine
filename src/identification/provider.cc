#include "identification/provider.hh"
#include "identification/tag.hh"

using namespace engine::identification;

provider::provider() {}

counter_type provider::peek() const noexcept { return _next; }

tag provider::obtain() {
  return {*this};
}

counter_type provider::get() { return this->_next++; }
