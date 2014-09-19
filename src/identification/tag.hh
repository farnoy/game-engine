#pragma once
#include "identification.hh"
#include <functional>

namespace engine {
namespace identification {
class provider;

struct tag {
  class provider const* provider;

  counter_type id;

  tag();

  tag(class provider& provider);

  ~tag();

  tag(const tag&);

  tag(tag&&);

  tag& operator=(const tag&);

  tag& operator=(tag&&);

  bool operator<(const tag&) const;

  bool operator==(const tag&) const;

  bool operator!=(const tag&) const;

  bool operator>(const tag&) const;

  bool is_empty() const;
};
}
}

namespace std {
template <>
struct hash<engine::identification::tag> {
  std::size_t operator()(engine::identification::tag const& tag) const {
    return std::hash<engine::identification::counter_type>()(tag.id);
  }
};
}
