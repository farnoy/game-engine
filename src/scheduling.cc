#include "scheduling.hh"

using engine::scheduling::tick_duration;
using engine::scheduling::ticks_count;

tick_duration engine::scheduling::get_duration_for(ticks_count ticks) {
  return tick_duration{ticks};
}
