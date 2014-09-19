#pragma once
#include <SFML/Window/Event.hpp>
#include "identification/tag.hh"
#include <vector>

namespace engine {
namespace identification {
struct tag;
}
class controller_manager;
class runner;

class controller {
  friend class controller_manager;
  identification::tag _tag;
  std::string const _type;
  std::vector<sf::Event::EventType> const _handled_events;

  void reset_tag();

 public:
  controller(std::string&& type, std::vector<sf::Event::EventType>&& events);
  virtual ~controller();

  identification::tag const& get_tag() const;

  bool is_registered() const;

  virtual bool handle(const sf::Event&, runner&);

  std::string const& get_type() const;

  bool is_handling(sf::Event::EventType const& ev_type) const;
};
}
