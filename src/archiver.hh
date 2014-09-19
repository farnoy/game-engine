#pragma once
#include <chrono>
#include <deque>
#include "frame.hh"
#include "scheduling.hh"

namespace std {
class logic_error;
}
namespace engine {
class runner;
class archiver {
  std::deque<frame> _frames;

 public:
  static constexpr std::chrono::seconds maximum_flashback{5};

  static constexpr auto maximum_flashback_frames =
      scheduling::tick_duration{maximum_flashback}.count();

  void archive(const runner&) noexcept;

  scheduling::tick_duration::rep count() const;

  bool apply(scheduling::ticks_count ticks, runner& runner) noexcept;

 protected:
  frame retrieve(scheduling::ticks_count ticks) noexcept(false);
};
}
