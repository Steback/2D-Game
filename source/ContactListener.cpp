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
    auto* bodyA = contact->GetFixtureA()->GetBody();
    auto* bodyB = contact->GetFixtureB()->GetBody();

    auto entityA = *static_cast<Entity*>(bodyA->GetUserData());
    auto entityB = *static_cast<Entity*>(bodyB->GetUserData());

    if ( entityA.type == PLAYER && entityB.type == ENEMY ) {
        gameOver = true;
    }

    if ( entityA.type == PLAYER && entityB.type == PROJECTILE ) {
        gameOver = true;
    }

    if ( entityA.type == HELIPORT && entityB.type == PLAYER ) {
        gameOver = true;
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

bool ContactListener::GameOver() const {
    return gameOver;
}
