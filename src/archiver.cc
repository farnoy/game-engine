#include <glog/logging.h>
#include <ostream>
#include <stdexcept>
#include "archiver.hh"
#include "frame.hh"

namespace engine {
class runner;
}

using namespace engine;

void archiver::archive(const runner& _runner) noexcept {
  if (_frames.size() >= archiver::maximum_flashback_frames)
    _frames.pop_back();
  _frames.emplace_front(_runner);
}

bool archiver::apply(scheduling::ticks_count ticks_ago, runner& _runner) noexcept {
  try {
    this->retrieve(ticks_ago).replay(_runner);
  }
  catch (std::logic_error& e) {
    DLOG(WARNING) << e.what();
    return false;
  }

  return true;
}

frame archiver::retrieve(scheduling::ticks_count ticks_ago) noexcept(false) {
  if (ticks_ago >= _frames.size()) {
    if (ticks_ago != _frames.size())
      throw std::logic_error("Flashback limit reached");
    frame ret = _frames.front();
    _frames.clear();
    return ret;
    ;
  }
  // correct assumption: ticks_ago < _frames.size()

  if (ticks_ago > 1) {
    auto i = ticks_ago - 1;  // we need to destroy history until that frame
    auto it = _frames.begin() + i;

    _frames.erase(_frames.begin(), it);
  }

  frame requested_frame{_frames.front()};
  _frames.pop_front();  // leave older frames intact
  return requested_frame;
}

scheduling::tick_duration::rep archiver::count() const { return this->_frames.size(); }
