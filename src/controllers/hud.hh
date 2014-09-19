#pragma once
#include "controller.hh"
#include <map>
#include <vector>
#include <SFML/Graphics/Transformable.hpp>

namespace engine {
namespace controllers {
class hud : public controller {
 public:
  enum class positioning {
    bottom
  };

  static const unsigned short element_spacing = 50;  // pixels

 private:
  std::map<positioning, std::vector<sf::Transformable*> > _elements;

 public:
  hud();

  virtual bool handle(const sf::Event& event, runner& runner) override;

  void handle(positioning p, sf::Transformable* t);
};
}
}
