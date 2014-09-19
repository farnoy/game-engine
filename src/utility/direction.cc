#include "utility/direction.hh"

using engine::utility::direction;

// not sure so check it
static_assert(char(1) == char(direction::north), "Wrong bitflags");
static_assert(char(2) == char(direction::south), "Wrong bitflags");
static_assert(char(4) == char(direction::east), "Wrong bitflags");
static_assert(char(8) == char(direction::west), "Wrong bitflags");
