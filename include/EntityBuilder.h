#include"Components.h"

class EntityBuilder 
{
private:
    Entity& entity;

public:
    EntityBuilder(Entity& e) : entity(e) {}

    EntityBuilder& withTransform(float x, float y, int width, int height, int scale);

    EntityBuilder& withSprite(const std::string& textureID, bool animated, const std::vector<Animation>& animations);

    EntityBuilder& withHealth(int health);

    EntityBuilder& withKeyboardController();

    EntityBuilder& withCollider(const std::string& tag);

    EntityBuilder& withAI(Entity& target, Vector2D& targetPosition, SDL_Rect& targetCollider, SDL_Rect& entityCollider);

    EntityBuilder& inGroup(Group group);
};
