#ifndef COLLISION_COMPONENT_HPP
#define COLLISION_COMPONENT_HPP

#include <box2d/box2d.h>
#include "box2d/b2_shape.h"
#include "fmt/core.h"

#include "../Constants.hpp"
#include "../Game.hpp"
#include "../ContactListener.hpp"

class CollisionComponent {
    public:
        b2PolygonShape polygon;
        b2Body* body;
        b2BodyDef bodyDef;
        b2FixtureDef boxShapeDef;

        CollisionComponent(b2Vec2 size_, b2Vec2 position_, EntityType type_) {
            polygon.SetAsBox(size_.x / 2, size_.y / 2);

            bodyDef.type = ( type_ == PLAYER ? b2_dynamicBody : b2_staticBody );
            bodyDef.position = position_;
            bodyDef.angle = 0.0f;

            body = Game::contactListener->CreateBody(&bodyDef);

            boxShapeDef.shape = &polygon;
            boxShapeDef.density = 1.0f;
            boxShapeDef.restitution = 0.1f;

            boxShapeDef.filter.categoryBits = ( type_ == PLAYER ? PLAYER_CATEGORY : ENEMY_CATEGORY );
            boxShapeDef.filter.maskBits = ( type_ == PLAYER ? PLAYER_MASK : ENEMY_MASK );
            boxShapeDef.filter.groupIndex = COLLIDE;

            body->CreateFixture(&boxShapeDef);
        }

        ~CollisionComponent() = default;

        void update(b2Vec2 position_) {
            body->SetTransform(position_, 0.0f);
        }
};

#endif
