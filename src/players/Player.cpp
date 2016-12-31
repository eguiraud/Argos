#include "Player.h"
#include <level/Level.h>

Character::Character(Level &level, float x, float y) {
  level_ = &level;
  texture.loadFromFile("player.png");

  b2BodyDef BodyDef;
  BodyDef.position = b2Vec2(x / SCALE, y / SCALE);
  BodyDef.type = b2_dynamicBody;
  BodyDef.fixedRotation = true;
  Body = level.World.CreateBody(&BodyDef);

  level.World.SetContactListener(&level.hasContact);

  b2CircleShape Shape;
  Shape.m_p.Set(0, 0);
  Shape.m_radius = radius;

  b2FixtureDef FixtureDef;
  FixtureDef.density = 1.f;
  FixtureDef.friction = 0.0f;
  FixtureDef.shape = &Shape;
  FixtureDef.userData = (void *) this;
  FixtureDef.filter.categoryBits = B2D_PLAYER;
  FixtureDef.filter.maskBits = B2D_ENEMY | B2D_ITEM | B2D_LEVEL;
  Body->CreateFixture(&FixtureDef);
  Body->SetUserData((void*)this);
}

Tile &Character::getTile(int dx, int dy) {
  int tx = (int) (Body->GetPosition().x + 0.5f) + dx;
  int ty = (int) (Body->GetPosition().y + 0.5f) + dy;
  return level_->get(tx, ty);
}

float Character::getYSpeed() {
  return Body->GetLinearVelocity().y;
}