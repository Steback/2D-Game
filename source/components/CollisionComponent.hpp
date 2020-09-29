#ifndef COLLISION_COMPONENT_HPP
#define COLLISION_COMPONENT_HPP

#include "box2d/box2d.h"
#include "box2d/b2_shape.h"
#include "fmt/core.h"

#include "../Constants.hpp"
#include "../Game.hpp"
#include "../ContactListener.hpp"
#include "../EntityManager.hpp"

class CollisionComponent {
    public:
        b2Body* body;
        b2PolygonShape polygon;

        CollisionComponent(b2Vec2 size_, b2Vec2 position_, unsigned int entityID_) {
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.position.Set(position_.x, position_.y);
            bodyDef.angle = 0.0f;

            body = Game::contactListener->CreateBody(&bodyDef);

            polygon.SetAsBox(size_.x / 2, size_.y / 2);

            b2FixtureDef boxShapeDef;
            boxShapeDef.shape = &polygon;
            boxShapeDef.density = 1.0f;
            boxShapeDef.restitution = 0.1f;

            body->SetUserData(static_cast<void*>(&Game::entityManager->getEntity(entityID_)));

            body->CreateFixture(&boxShapeDef);
        }

        ~CollisionComponent() = default;

        void update(b2Vec2 position_) const {
            body->SetTransform(position_, body->GetAngle());
        }
};

#endif
