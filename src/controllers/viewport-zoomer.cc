#include <glog/logging.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "runner.hh"
#include "renderer.hh"
#include "controllers/viewport-zoomer.hh"

using engine::controllers::viewport_zoomer;
using engine::runner;
using engine::scheduling::ticks_count;

static sf::Vector2f ease_in(sf::Vector2f start,
                            sf::Vector2f end,
                            ticks_count current_iter,
                            ticks_count max_iter) {
  float progress = static_cast<float>(current_iter) / max_iter;
  auto diff = end - start;
  diff *= progress;
  return start + diff;
}

viewport_zoomer::viewport_zoomer()
    : controller{"viewport-zoomer", {sf::Event::MouseWheelMoved, sf::Event::Count}} {}

bool viewport_zoomer::handle(const sf::Event& event, runner& runner) {
  auto& view = runner.get_renderer().get_layer("Foreground").get_view();
  if (event.type == sf::Event::MouseWheelMoved) {
    this->_starting_size = view.getSize();
    this->_transition_timer = 0;

    // Calculate the new factor
    this->set_factor_with_delta(event.mouseWheel.delta);
    LOG(INFO) << "New Zoom factor: " << this->_factor;
  } else if (this->_transition_timer <= 60) {  // Count
    this->_transition_timer++;
    auto window = runner.get_renderer().get_window();
    // this can break when doing resizing :<
    auto new_size = window->getDefaultView().getSize() * this->get_factor_for_scaling();
    view.setSize(ease_in(this->_starting_size, new_size, this->_transition_timer, 60));
  }

  return true;
}

void viewport_zoomer::set_factor_with_delta(float delta) {
  this->_factor = std::min(3.f, std::max(0.3f, this->_factor + (delta * 0.1f)));
}

float viewport_zoomer::get_factor_for_scaling() const { return 1.f / this->_factor; }
