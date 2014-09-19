#pragma once
#include <map>
#include <memory>
#include <tuple>
#include <SFML/Window/Event.hpp>
#include "identification/provider.hh"

namespace engine {
class controller;
class runner;

namespace identification {
class provider;
struct tag;
}

class controller_manager {
 public:
  using controllers = std::map<identification::tag, std::shared_ptr<controller> >;

  using evaluation_tree = std::multimap<sf::Event::EventType, std::shared_ptr<controller> >;

 private:
  controllers _controllers;
  identification::provider _idprovider;
  evaluation_tree _evaluation_tree;

 public:
  using evaluation_path =
      std::tuple<evaluation_tree::const_iterator, evaluation_tree::const_iterator>;

  controller_manager();

  controller_manager(controller_manager const&) = delete;

  controller_manager(controller_manager&&);

  controller_manager& operator=(const controller_manager&) = delete;

  controller_manager& operator=(controller_manager&&);

  bool has(std::string const&) const noexcept;

  std::weak_ptr<controller> get_by_type(std::string const&) noexcept;

  std::weak_ptr<controller const> get_by_type(std::string const&) const noexcept;

  identification::tag attach(std::shared_ptr<controller> controller);

  std::shared_ptr<controller> detach(identification::tag const& tag);

  std::shared_ptr<controller> detach(std::shared_ptr<const controller>);

  unsigned short evaluate(const sf::Event& event, runner& runner);
};
}
