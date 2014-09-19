#include <glog/logging.h>
#include <algorithm>
#include <ostream>
#include <type_traits>
#include "scheduler.hh"

using engine::scheduler;
using engine::scheduling::ticks_count;
using engine::scheduling::clock_type;
using engine::scheduling::tick_duration;

scheduler::scheduler() { this->_last_update = clock_type::now(); }

clock_type::time_point scheduler::next_update() const noexcept {
  return this->_last_update +
         std::chrono::duration_cast<scheduling::clock_type::duration>(scheduling::tick_duration{1});
}

clock_type::time_point scheduler::last_update() const noexcept { return _last_update; }

ticks_count scheduler::update() noexcept {
  auto now = clock_type::now();
  auto diff = now - this->_last_update;

  this->_last_update = now;
  if (this->_stopped)
    return 0;

  auto ticks = std::chrono::duration_cast<tick_duration>(diff).count();

  DLOG_IF(WARNING, ticks > 1) << "Running late, updating " << ticks << " ticks";

  return ticks;
}

bool scheduler::is_late() const {
  auto diff = clock_type::now() - this->next_update();
  return (diff > diff.zero());
}

void scheduler::stop() { this->_stopped = true; }

void scheduler::start() {
  this->_stopped = false;
  // this->_last_update = scheduler::clock_type::now();
}

bool scheduler::is_stopped() const { return this->_stopped; }

bool scheduler::toggle_reverse() { return this->_reversed = !this->_reversed; }

bool scheduler::is_reverse() const { return this->_reversed; }
