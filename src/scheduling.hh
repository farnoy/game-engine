#pragma once
#include <ratio>
#include <chrono>

namespace engine {
namespace scheduling {
using clock_type = std::chrono::steady_clock;
using update_frequency = std::ratio<1, 60>;
using ticks_count = unsigned short;
using tick_duration = std::chrono::duration<ticks_count, update_frequency>;

tick_duration get_duration_for(ticks_count ticks);
}
}
