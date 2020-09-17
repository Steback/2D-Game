#ifndef CONTACT_LISTENER_HPP
#define CONTACT_LISTENER_HPP

#include <memory>
#include <map>

#include "box2d/box2d.h"
#include "box2d/b2_contact.h"

#include "Constants.hpp"

class ContactListener : public b2ContactListener {
    public:
        ContactListener();
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
        b2Body* CreateBody(const b2BodyDef *def);
        void DestroyBody(b2Body* body);
        void Step(float timeStep, int32 velocityIterations, int32 positionIterations);

    private:
        std::unique_ptr<b2World> world;
};

#endif
