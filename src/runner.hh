#pragma once
#include <memory>
#include "identification/tag.hh"
#include "controller-manager.hh"

namespace engine {
class entity_manager;
class renderer;
class controller_manager;
class scheduler;
class archiver;

class runner {
  std::shared_ptr<entity_manager> _entity_manager;
  std::shared_ptr<controller_manager> _controller_manager;
  std::shared_ptr<scheduler> _scheduler;
  std::shared_ptr<renderer> _renderer;
  std::shared_ptr<archiver> _archiver;

 public:
  runner();

  runner(std::shared_ptr<renderer>);

  runner(const runner&) = delete;

  runner(runner&&) = delete;

  runner& operator=(const runner&) = delete;

  runner& operator=(runner&&) = delete;

  void run();

  template <class Controller, class... Args>
  identification::tag attach_controller(Args&&... args) {
    auto controller = std::make_shared<Controller>(std::forward<Args>(args)...);
    auto tag = this->_controller_manager->attach(controller);
    return tag;
  }

  identification::tag attach_controller(std::shared_ptr<engine::controller> controller);

  std::shared_ptr<engine::controller> detach_controller(identification::tag const& tag);

  controller_manager const& get_controller_manager() const;

  controller_manager& get_controller_manager();

  renderer& get_renderer();

  archiver const& get_archiver() const;

  entity_manager& get_entity_manager();

  entity_manager const& get_entity_manager() const;

  scheduler& get_scheduler();
};
}
