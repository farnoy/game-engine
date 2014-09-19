#include "identification/tag.hh"
#include <stdexcept>
#include "identification/provider.hh"

using namespace engine::identification;

tag::tag(class provider& prov) : provider(&prov), id(prov.get()) {}

tag::tag(const tag& other) : provider(other.provider), id(other.id) {}

tag::tag(tag&& other) : provider(std::move(other.provider)), id(std::move(other.id)) {}

tag::tag() : provider(nullptr), id(0) {}

bool tag::is_empty() const { return this->provider == nullptr || this->id == 0; }

tag::~tag() {}

tag& tag::operator=(const tag& other) {
  this->provider = other.provider;
  this->id = other.id;
  return *this;
}

tag& tag::operator=(tag&& other) {
  this->provider = std::move(other.provider);
  this->id = std::move(other.id);
  return *this;
}

bool tag::operator<(const tag& other) const { return this->id < other.id; }

bool tag::operator>(const tag& other) const { return this->id > other.id; }

bool tag::operator==(const tag& other) const {
  return this->id == other.id && this->provider == other.provider;
}

bool tag::operator!=(const tag& other) const {
  return this->id != other.id || this->provider != other.provider;
}
