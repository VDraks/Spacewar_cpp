#include "gtest/gtest.h"

#include "game/components/collider.h"
#include "game/components/events/entities_collided.h"
#include "game/systems/physics/collision_system.h"
#include "model/components/transform.h"

using namespace game::system;
using namespace game::component;
using namespace model::component;

namespace {

class CollisionSystemTest : public ::testing::Test {
public:
    void SetUp() override {
        EXPECT_EQ(0, entityManager.getEntitySet<event::EntitiesCollided>().getSize());
    }

protected:
    ecs::EntityManager entityManager;

    constexpr static float colliderRadius = 10.f;

    ecs::Entity addCollider(math::Vec2 pos) {
        auto entity = entityManager.createEntity();
        auto& transform = entityManager.addComponent<Transform>(entity);
        transform.position = pos;
        auto& collider = entityManager.addComponent<Collider>(entity);
        collider.radius = colliderRadius;
        return entity;
    }
};

} // namespace

TEST_F(CollisionSystemTest, EmptyTest) {
    CollisionSystem collisionSystem;
    collisionSystem.update(1.f, entityManager);
    EXPECT_EQ(0, entityManager.getEntitySet<event::EntitiesCollided>().getSize());
}

TEST_F(CollisionSystemTest, OneCollider) {
    CollisionSystem collisionSystem;
    addCollider({0.f, 0.f});
    collisionSystem.update(1.f, entityManager);
    EXPECT_EQ(0, entityManager.getEntitySet<event::EntitiesCollided>().getSize());
}

TEST_F(CollisionSystemTest, CollidersCollision) {
    EXPECT_EQ(0, entityManager.getEntitySet<Collider>().getSize());
    CollisionSystem collisionSystem;

    addCollider({0.f, 0.f});
    const auto secondEntity = addCollider({100.f, 0.f});
    collisionSystem.update(1.f, entityManager);
    EXPECT_EQ(0, entityManager.getEntitySet<event::EntitiesCollided>().getSize());

    entityManager.getComponent<Transform>(secondEntity).position.x = 10.f;
    collisionSystem.update(1.f, entityManager);
    EXPECT_EQ(1, entityManager.getEntitySet<event::EntitiesCollided>().getSize());
}