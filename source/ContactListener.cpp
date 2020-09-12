#include "fmt/core.h"

#include "ContactListener.hpp"

ContactListener::ContactListener() {
    world = std::make_unique<b2World>(b2Vec2_zero);
    world->SetContactListener(this);
}

void ContactListener::BeginContact(b2Contact *contact) {
    B2_NOT_USED(contact);
}

void ContactListener::EndContact(b2Contact *contact) {
    B2_NOT_USED(contact);
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
    const b2Manifold* manifold = contact->GetManifold();

    if (manifold->pointCount == 0)
    {
        return;
    }

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
    b2GetPointStates(state1, state2, oldManifold, manifold);

    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);

    for (int32 i = 0; i < manifold->pointCount && m_pointCount < 10 ; ++i)
    {
        ContactPoint* cp = m_points + m_pointCount;
        cp->fixtureA = fixtureA;
        cp->fixtureB = fixtureB;
        cp->position = worldManifold.points[i];
        cp->normal = worldManifold.normal;
        cp->state = state2[i];
        cp->normalImpulse = manifold->points[i].normalImpulse;
        cp->tangentImpulse = manifold->points[i].tangentImpulse;
        cp->separation = worldManifold.separations[i];
        ++m_pointCount;
    }
}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
    B2_NOT_USED(contact);
}

b2Body *ContactListener::CreateBody(const b2BodyDef *def) {
    return world->CreateBody(def);
}

void ContactListener::DestroyBody(b2Body *body) {
    world->DestroyBody(body);
}
