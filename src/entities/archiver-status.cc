#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include "entities/archiver-status.hh"
#include "utility/angles.hh"
#include "controllers/physics.hh"
#include "controllers/hud.hh"
#include "archiver.hh"
#include "runner.hh"

using namespace engine::entities;
using engine::utility::angles::type;

archiver_status::archiver_status(runner& _runner)
    : _bar(new sf::RectangleShape), _archiver(_runner.get_archiver()) {
  this->_bar->setFillColor(sf::Color::Black);
  this->_bar->setOutlineThickness(3.f);
  this->_bar->setOutlineColor(sf::Color::White);

  if (_runner.get_controller_manager().has("hud")) {
    auto hud = std::static_pointer_cast<engine::controllers::hud>(
        _runner.get_controller_manager().get_by_type("hud").lock());
    hud->handle(engine::controllers::hud::positioning::bottom, this->_bar.get());
  }
}

void archiver_status::draw(sf::RenderTarget& target) {
  this->_bar->setSize({static_cast<float>(this->_archiver.count()) * 2, 10.f});
  this->_bar->setOrigin(this->_bar->getSize() / 2.f);
  target.draw(*this->_bar);
}

void archiver_status::update(scheduling::ticks_count /* ticks */) {}

engine::entity* archiver_status::copy() const {
  auto cv_lifted = const_cast<archiver_status*>(this);
  return static_cast<entity*>(cv_lifted);
}
