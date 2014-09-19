#include <SFML/Window/Event.hpp>
#include <iostream>
#include <glog/logging.h>
#include <algorithm>
#include <ostream>
#include "controller.hh"
#include "controller-manager.hh"
#include "identification/provider.hh"
#include "identification/tag.hh"

using namespace engine;

controller_manager::controller_manager() {}

identification::tag controller_manager::attach(std::shared_ptr<controller> cont) {
  auto tag = this->_idprovider.obtain();
  this->_controllers.emplace(tag, cont);

  // Optimize by keeping separate execution path for every event type
  auto handled_events = cont->_handled_events;
  for (auto handled_event : handled_events)
    this->_evaluation_tree.emplace(handled_event, cont);

  cont->_tag = tag;
  // cont->on_attach(*this);
  return cont->_tag;
}

std::shared_ptr<controller> controller_manager::detach(identification::tag const& tag) {
  if (tag.is_empty())
    return nullptr;

  // reverse_iterator is hard :()
  auto it = std::find_if(
      this->_controllers.begin(),
      this->_controllers.end(),
      [&tag](std::pair<identification::tag const&, std::shared_ptr<controller const> > pair)
          ->bool { return pair.first == tag; });

  if (it == this->_controllers.end()) {
    DLOG(WARNING) << "detach() requested on a bad tag: " << tag.id;
    return nullptr;
  }

  auto cont = std::get<1>(*it);
  auto handled_events = cont->_handled_events;
  for (auto handled_event : handled_events) {
    auto range = this->_evaluation_tree.equal_range(handled_event);
    // this will NOT work when fucked up controllers register same event more
    // than one time...
    auto it = std::find_if(
        range.first,
        range.second,
        [&cont](std::pair<const sf::Event::EventType, const std::shared_ptr<controller> > c)
            ->bool { return c.second == cont; });
    this->_evaluation_tree.erase(it);
  }
  this->_controllers.erase(it);
  cont->reset_tag();
  // cont->on_detach(*this);

  return cont;
}

std::shared_ptr<controller> controller_manager::detach(std::shared_ptr<const controller> cont) {
  return this->detach(cont->get_tag());
}

bool controller_manager::has(std::string const& type) const noexcept {
  auto it = std::find_if(
      this->_controllers.begin(),
      this->_controllers.end(),
      [&](std::pair<identification::tag const&, std::shared_ptr<controller const> > pair)
          ->bool { return pair.second->get_type() == type; });

  return it != this->_controllers.end();
}

unsigned short controller_manager::evaluate(const sf::Event& event, runner& _runner) {
  unsigned short count = 0;
  // propagating when controller requests it
  auto declared_controllers = this->_evaluation_tree.equal_range(event.type);
  auto last = declared_controllers.second;
  auto it = declared_controllers.first;
  while (it != last) {
    auto controller = it->second;
    it++;
    count++;
    // if we break in the next statement, contract to return [first, last)
    // is fulfilled by the incremented iterator
    if (!controller->handle(event, _runner))
      break;
  }

  return count;
}

std::weak_ptr<controller> controller_manager::get_by_type(std::string const& type) noexcept {
  auto it = std::find_if(
      this->_controllers.begin(),
      this->_controllers.end(),
      [&](std::pair<identification::tag const&, std::shared_ptr<controller const> > pair)
          ->bool { return pair.second->get_type() == type; });

  if (it != this->_controllers.end())
    return {it->second};
  else
    return {};
}

std::weak_ptr<controller const> controller_manager::get_by_type(std::string const& type) const
    noexcept {
  auto it = std::find_if(
      this->_controllers.begin(),
      this->_controllers.end(),
      [&](std::pair<identification::tag const&, std::shared_ptr<controller const> const&> pair)
          ->bool { return pair.second->get_type() == type; });

  if (it != this->_controllers.end())
    return {it->second};
  else
    return {};
}
