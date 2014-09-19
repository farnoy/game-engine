#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include "entities/testcircle.hh"
#include "controllers/physics.hh"
#include "utility/angles.hh"
#include <Box2D/Box2D.h>

using namespace engine::entities;
using engine::utility::angles::type;
using engine::controllers::physics;

testcircle::testcircle(struct physics& physics,
                       const sf::Vector2f& origin,
                       angle<type::radian> _angle)
    : shape(new sf::CircleShape(35)), _angle(_angle), physics(physics) {
  this->shape->setOrigin(35, 35);
  this->shape->setPosition(origin);
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(origin.x / 64.f, origin.y / 64.f);
  this->body = this->physics.world.CreateBody(&bodyDef);
  b2CircleShape shape;
  shape.m_radius = 35.f / 64.f;
  ;
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.f;
  fixtureDef.friction = 0.8f;
  fixtureDef.restitution = 0.7f;
  body->CreateFixture(&fixtureDef);
}

testcircle::testcircle(const testcircle& other)
    : shape(new sf::CircleShape(*other.shape)),
      _angle(other._angle),
      physics(other.physics),
      body(other.body) {}

void testcircle::draw(sf::RenderTarget& target) { target.draw(*this->shape); }

void testcircle::update(scheduling::ticks_count /* ticks */) {
  auto position = this->body->GetPosition();
  position *= 64;
  this->shape->setPosition(position.x, position.y);
}

engine::entity* testcircle::copy() const { return new testcircle(*this); }
