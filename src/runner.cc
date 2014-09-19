#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <glog/logging.h>
#include <chrono>
#include <ostream>
#include <thread>
#include "controller.hh"
#include "renderer.hh"
#include "runner.hh"
#include "controller-manager.hh"
#include "entity-manager.hh"
#include "archiver.hh"
#include "scheduler.hh"

using namespace engine;

runner::runner() : runner(std::make_shared<renderer>()) {}

runner::runner(std::shared_ptr<renderer> renderer)
    : _entity_manager(std::make_shared<entity_manager>()),
      _controller_manager(std::make_shared<controller_manager>()),
      _scheduler(std::make_shared<scheduler>()),
      _renderer(renderer),
      _archiver(std::make_shared<archiver>()) {}

// This whole loop needs to be threadsafe with entity_manager if we're archiving
void runner::run() {
  while (_renderer->is_window_open()) {
    if (_scheduler->is_late()) {
      auto ticks = _scheduler->update();

      sf::Event event;
      while (_renderer->get_window()->pollEvent(event)) {
        _controller_manager->evaluate(event, *this);
      }
      event.type = sf::Event::Count;
      _controller_manager->evaluate(event, *this);

      DLOG_IF(WARNING, ticks == 0) << "ASSUMPTION ticks != 0 after #is_late() IS WRONG";

      if (!this->_scheduler->is_stopped()) {
        if (!this->_scheduler->is_reverse()) {
          _archiver->archive(*this);
          _entity_manager->update(ticks);
        } else {
          if (!_archiver->apply(ticks, *this))
            this->_scheduler->toggle_reverse();
        }
      }
      _renderer->render(*_entity_manager);
    } else
      std::this_thread::sleep_until(_scheduler->next_update());
  }
}

identification::tag runner::attach_controller(std::shared_ptr<engine::controller> controller) {
  return this->_controller_manager->attach(controller);
}

std::shared_ptr<engine::controller> runner::detach_controller(identification::tag const& tag) {
  return this->_controller_manager->detach(tag);
}

controller_manager const& runner::get_controller_manager() const { return *_controller_manager; }

controller_manager& runner::get_controller_manager() { return *_controller_manager; }

renderer& runner::get_renderer() { return *_renderer; }

archiver const& runner::get_archiver() const { return *_archiver; }

entity_manager& runner::get_entity_manager() { return *_entity_manager; }

entity_manager const& runner::get_entity_manager() const { return *_entity_manager; }

scheduler& runner::get_scheduler() { return *_scheduler; }
