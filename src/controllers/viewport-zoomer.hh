#pragma once
#include "controller.hh"
#include "scheduling.hh"

namespace engine {
namespace controllers {
class viewport_zoomer : public controller {
  float _factor{1};
  scheduling::ticks_count _transition_timer;
  sf::Vector2f _starting_size;

 public:
  viewport_zoomer();

  virtual bool handle(const sf::Event& event, runner& runner) override;

  void set_factor_with_delta(float delta);

  float get_factor_for_scaling() const;
};
}
}
