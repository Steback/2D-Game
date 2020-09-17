#include "fmt/core.h"

#include "EntityManager.hpp"
#include "ContactListener.hpp"

ContactListener::ContactListener() {
    world = std::make_unique<b2World>(b2Vec2(0.0f, -10.0f));
    world->SetContactListener(this);
}

void ContactListener::BeginContact(b2Contact *contact) {
    B2_NOT_USED(contact);
}

void ContactListener::EndContact(b2Contact *contact) {
    B2_NOT_USED(contact);
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
//    b2WorldManifold worldManifold;
//    contact->GetWorldManifold(&worldManifold);
//
//    b2PointState state1[2], state2[2];
//    b2GetPointStates(state1, state2, oldManifold, contact->GetManifold());

    auto* bodyA = contact->GetFixtureA()->GetBody();
    auto* bodyB = contact->GetFixtureB()->GetBody();

    auto entityTypeA = *static_cast<EntityType*>(bodyA->GetUserData());
    auto entityTypeB = *static_cast<EntityType*>(bodyB->GetUserData());

    if ( entityTypeA == PLAYER && entityTypeB == ENEMY ) {
        fmt::print("GAME OVER!\n");
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

void ContactListener::Step(float timeStep_, int32 velocityIterations_, int32 positionIterations_) {
    world->Step(timeStep_, velocityIterations_, positionIterations_);
}
