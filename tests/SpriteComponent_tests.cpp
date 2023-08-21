#include "UnitTest++/UnitTest++.h"
#include "Components.h"

class SpriteComponentTestable : public SpriteComponent
{
public:
    using SpriteComponent::animated;
    using SpriteComponent::frames;
    using SpriteComponent::speed;
    using SpriteComponent::animIndex;
    using SpriteComponent::transform;
    using SpriteComponent::texture;
    using SpriteComponent::srcRect;
    using SpriteComponent::destRect;
};

SUITE(SpriteComponentTests)
{
    TEST(SpriteComponent_SetTexture)
    {
        Manager manager;
        auto& entity(manager.addEntity());

        SpriteComponentTestable spriteComponent;
        spriteComponent.entity = &entity;

        const std::string expectedTextureID = "player";

        spriteComponent.setTex(expectedTextureID);

        SDL_Texture* loadedTexture = spriteComponent.texture;
        SDL_Texture* expectedTexture = Game::assets->GetTexture(expectedTextureID);

        CHECK_EQUAL(expectedTexture, loadedTexture);
    }

    TEST(SpriteComponent_PlayAnimation)
    {
        Manager manager;
        auto& entity(manager.addEntity());

        SpriteComponentTestable spriteComponent;
        spriteComponent.entity = &entity;

        Animation idleAnimation("Idle", 0, 4, 100);
        spriteComponent.animations.emplace(idleAnimation.name, idleAnimation);

        spriteComponent.Play("Idle");

        CHECK_EQUAL("Idle", spriteComponent.CurrentlyPlaying());
    }

    TEST(SpriteComponent_Update)
    {
        Manager manager;
        auto& entity(manager.addEntity());
        entity.addComponent<TransformComponent>();

        SpriteComponentTestable spriteComponent;
        spriteComponent.entity = &entity;
        spriteComponent.animated = true; 
        spriteComponent.frames = 4; 
        spriteComponent.speed = 100; 
        spriteComponent.animIndex = 1;

        int currentFrame = (SDL_GetTicks() / spriteComponent.speed) % spriteComponent.frames;

        SDL_Texture* newTexture = NULL;
        spriteComponent.texture = newTexture;
        spriteComponent.transform = &entity.getComponent<TransformComponent>();

     
        spriteComponent.srcRect = { 0, 0, 32, 32 };
        spriteComponent.destRect = { 0, 0, 32, 32 };


        spriteComponent.update();

        SDL_Rect expectedSrcRect;

        expectedSrcRect.w = spriteComponent.transform->width;
        expectedSrcRect.h = spriteComponent.transform->height;
        
        expectedSrcRect.x = expectedSrcRect.w * currentFrame;
        expectedSrcRect.y = spriteComponent.animIndex * spriteComponent.transform->height;

        CHECK_EQUAL(expectedSrcRect.x, spriteComponent.srcRect.x);
        CHECK_EQUAL(expectedSrcRect.y, spriteComponent.srcRect.y);
        CHECK_EQUAL(expectedSrcRect.w, spriteComponent.srcRect.w);
        CHECK_EQUAL(expectedSrcRect.h, spriteComponent.srcRect.h);
    }
}
