#include <algorithm>
#include "controller.hh"

using namespace engine;

controller::controller(std::string&& type, std::vector<sf::Event::EventType>&& events)
    : _type(type), _handled_events(events) {}

controller::~controller() {}

identification::tag const& controller::get_tag() const { return this->_tag; }

void controller::reset_tag() {
  this->_tag = engine::identification::tag{};
}

// FIXME
bool controller::is_registered() const { return !this->_tag.is_empty(); }

bool controller::handle(const sf::Event& /* ev */, runner& /* runner */) {
  return true;  // bubble that shit - continue evaluation
}

std::string const& controller::get_type() const { return this->_type; }

bool controller::is_handling(sf::Event::EventType const& ev_type) const {
  return std::find(this->_handled_events.begin(), this->_handled_events.end(), ev_type) !=
         this->_handled_events.end();
}

/*
void controller::on_attach(const controller_manager&) {}
void controller::on_detach(const controller_manager&) {}
*/
