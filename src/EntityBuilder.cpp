#include "EntityBuilder.h"
#include "Components.h"


EntityBuilder& EntityBuilder::withTransform(float x, float y, int width, int height, int scale) 
{
    entity.addComponent<TransformComponent>(x, y, width, height, scale);
    return *this;
}

EntityBuilder& EntityBuilder::withSprite(const std::string& textureID, bool animated, const std::vector<Animation>& animations)
{
    entity.addComponent<SpriteComponent>(textureID, animated, animations);
    return *this;
}

EntityBuilder& EntityBuilder::withHealth(int health)
{
    entity.addComponent<HealthComponent>(health);
    return *this;
}

EntityBuilder& EntityBuilder::withKeyboardController()
{
    entity.addComponent<KeyboardController>();
    return *this;
}

EntityBuilder& EntityBuilder::withCollider(const std::string& tag)
{
    entity.addComponent<ColliderComponent>(tag);
    return *this;
}

EntityBuilder& EntityBuilder::withAI(Entity& target, Vector2D& targetPosition, SDL_Rect& targetCollider, SDL_Rect& entityCollider)
{
    entity.addComponent<AIComponent>(target, targetPosition, targetCollider, entityCollider);
    return *this;
}

EntityBuilder& EntityBuilder::inGroup(Group group)
{
    entity.addGroup(group);
    return *this;
}
