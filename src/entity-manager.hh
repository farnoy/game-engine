
#pragma once
#include <memory>
#include <unordered_map>
#include "scheduling.hh"
#include "identification/tag.hh"

namespace std {
class runtime_error;
}

namespace engine {
namespace identification {
struct tag;
class provider;
}
class entity;
class entity_manager {
 public:
  using entities = std::unordered_map<identification::tag, std::shared_ptr<entity> >;

  entity_manager();

  entity_manager(entity_manager const&);

  entity_manager(entity_manager&&);

  entity_manager& operator=(entity_manager const&);

  entity_manager& operator=(entity_manager&&);

  identification::tag add(std::shared_ptr<entity> entity) noexcept;

  std::shared_ptr<entity> remove(std::shared_ptr<entity> entity) noexcept;

  bool has(identification::tag const& tag) const;

  entities::iterator begin();

  entities::iterator end();

  void update(scheduling::ticks_count ticks_count);

  std::weak_ptr<entity> get_entity_by_tag(identification::tag const& tag);

 private:
  std::shared_ptr<identification::provider> _idprovider;
  entities _entities;
};
}
