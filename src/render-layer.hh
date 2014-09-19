#pragma once
#include <set>
#include <SFML/Graphics/View.hpp>

namespace sf {
class View;
}

namespace engine {
class renderer;

class render_layer {
  renderer& _renderer;
  std::string _name;
  std::set<identification::tag> _entities;
  sf::View _view;

  render_layer(renderer&, std::string);
  friend class renderer;

 public:
  sf::View const& get_view() const;

  sf::View& get_view();

  void add(identification::tag tag);
};
}
