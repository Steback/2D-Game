#ifndef CONTACT_LISTENER_HPP
#define CONTACT_LISTENER_HPP

#include <memory>

#include "box2d/box2d.h"
#include "box2d/b2_contact.h"

struct ContactPoint {
    b2Fixture* fixtureA;
    b2Fixture* fixtureB;
    b2Vec2 normal;
    b2Vec2 position;
    b2PointState state;
    float normalImpulse;
    float tangentImpulse;
    float separation;
};

class ContactListener : public b2ContactListener {
    public:
        ContactListener();
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
        b2Body* CreateBody(const b2BodyDef* def);
        void DestroyBody(b2Body* body);

    private:
        std::unique_ptr<b2World> world;
        ContactPoint m_points[10];
        int32 m_pointCount;
};

#endif
