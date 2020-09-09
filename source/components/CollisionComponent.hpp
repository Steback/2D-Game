#ifndef COLLISION_COMPONENT_HPP
#define COLLISION_COMPONENT_HPP

#include <box2d/box2d.h>
#include "box2d/b2_shape.h"
#include "fmt/core.h"

#include "../Constants.hpp"
#include "../Game.hpp"

class CollisionComponent {
    public:
        b2PolygonShape polygon;
        LayerType layerType;
        b2Transform transform;
        b2FixtureDef boxShapeDef;
        b2BodyDef boxBodyDef;
        b2Body* body3{};
        b2Contact* contact{};

        CollisionComponent(LayerType layerType_, b2Vec2 size_, b2Vec2 center_) : layerType(layerType_) {
            polygon.SetAsBox(size_.x / 2, size_.y / 2);
            transform.Set(center_, 0.0f);

            boxShapeDef.shape = &polygon;
            boxShapeDef.density = 1.0f;
            boxShapeDef.restitution = 0.1f;

            boxShapeDef.filter.groupIndex = k_largeGroup;
            boxShapeDef.filter.categoryBits = k_boxCategory;
            boxShapeDef.filter.maskBits = k_boxMask;

            boxBodyDef.type = b2_dynamicBody;
            boxBodyDef.position.Set(center_.x, center_.y);

            body3 = Game::world->CreateBody(&boxBodyDef);
            body3->CreateFixture(&boxShapeDef);

        }

        ~CollisionComponent() = default;

        void update(b2Vec2 position_) {
//            polygon.m_centroid = position_;
            transform.Set(position_, 0.0f);

            if ( !polygon.Validate() ) {
                fmt::print(stderr, "Polygon is not valid!\n");
            }

            if ( layerType == PLAYER_LAYER ) {
                auto view = Game::entityManager->registry.view<CollisionComponent>();

                for ( auto entity : view ) {
                    auto cc = Game::entityManager->registry.get<CollisionComponent>(entity);

                    if ( cc.layerType != PLAYER_LAYER ) {
                        auto overlap = b2TestOverlap(&polygon, 4,
                                                     &cc.polygon, 4,
                                                     transform,
                                                     cc.transform);

                        if ( overlap ) {
                            fmt::print("FAAAACK\n");
                        }
                    }
                }
            }
        }
};

#endif
