#include <stdexcept>
#include <utility>
#include "entity-manager.hh"
#include "entity.hh"
#include "identification/tag.hh"
#include "identification/provider.hh"

using namespace engine;

entity_manager::entity_manager() : _idprovider(new identification::provider) {}

entity_manager::entity_manager(const entity_manager& other) : _idprovider(other._idprovider) {
  // this makes copies deeper than smart pointers, using entity::copy()
  for (auto ent : other._entities) {
    auto copied = ent.second->copy();
    if (copied) {
      if (copied == ent.second.get()) {
        // a.k.a "asked to not manage him twice while not wiping him from his
        // lifetime in the past"
        this->_entities.emplace(ent.first, ent.second);
      } else {
        copied->_tag = ent.first;
        this->_entities.emplace(ent.first, std::shared_ptr<entity>(copied));
      }
    }
  }
}

entity_manager::entity_manager(entity_manager&& other)
    : _idprovider(std::move(other._idprovider)), _entities(std::move(other._entities)) {}

entity_manager& entity_manager::operator=(const entity_manager& other) {
  if (this != &other) {
    for (auto ent : other._entities) {
      auto copied = ent.second->copy();
      if (copied)
        this->_entities.emplace(ent.first, std::shared_ptr<entity>(copied));
    }
    this->_idprovider = other._idprovider;
  }
  return *this;
}

entity_manager& entity_manager::operator=(entity_manager&& other) {
  if (this != &other) {
    this->_entities = std::move(other._entities);
    this->_idprovider = std::move(other._idprovider);
  }
  return *this;
}

identification::tag entity_manager::add(std::shared_ptr<entity> ent) noexcept {
  if (!ent)
    return {};
  if (!ent->get_tag().is_empty())
    return {};

  auto tag = _idprovider->obtain();
  ent->_tag = tag;

  this->_entities.emplace(tag, std::move(ent));

  return tag;
}

std::shared_ptr<entity> entity_manager::remove(std::shared_ptr<entity> ent) noexcept {
  if (!ent)
    return nullptr;
  if (ent->get_tag().provider != this->_idprovider.get())  // if it's registered elsewhere
    return nullptr;

  this->_entities.erase(ent->_tag);

  return ent;
}

bool entity_manager::has(identification::tag const& id) const {
  return this->_entities.find(id) != this->_entities.end();
}

entity_manager::entities::iterator entity_manager::begin() { return this->_entities.begin(); }
entity_manager::entities::iterator entity_manager::end() { return this->_entities.end(); }

void entity_manager::update(scheduling::ticks_count count) {
  for (auto entity : this->_entities)
    entity.second->update(count);
}

std::weak_ptr<entity> entity_manager::get_entity_by_tag(identification::tag const& tag) {
  auto it = this->_entities.find(tag);

  if (it == this->_entities.end())
    return {};

  return {(*it).second};
}
