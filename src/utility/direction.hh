#pragma once

namespace engine {
namespace utility {
enum direction : unsigned short {
  north = 1,
  south = 1 << 1,
  east = 1 << 2,
  west = 1 << 3
};
}
}
