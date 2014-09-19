#pragma once
#include "scheduling.hh"

namespace engine {
class scheduler {
  scheduling::clock_type::time_point _last_update;
  bool _stopped{false};

  bool _reversed{false};

 public:
  scheduler();

  scheduler(const scheduler&) = delete;

  scheduler(scheduler&& other) = default;

  scheduler& operator=(const scheduler&) = delete;

  scheduler& operator=(scheduler&& other) = default;

  scheduling::ticks_count update() noexcept;

  scheduling::clock_type::time_point next_update() const noexcept;

  scheduling::clock_type::time_point last_update() const noexcept;

  bool is_late() const;

  void stop();

  void start();

  bool is_stopped() const;

  bool toggle_reverse();

  bool is_reverse() const;
};
}
