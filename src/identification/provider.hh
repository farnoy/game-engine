#pragma once
#include "identification.hh"

namespace engine {
namespace identification {
struct tag;

class provider {
  friend struct tag;
  counter_type _next{1};

  counter_type get();

 public:
  provider();

  counter_type peek() const noexcept;

  tag obtain();
};
}
}
