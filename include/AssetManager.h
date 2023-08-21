#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS.h"
#include "SDL.h"

/**
 * @class AssetManager
 * @brief Manages game assets such as textures and projectiles.
 */
class AssetManager
{
public:
    /**
     * @brief Constructor for the AssetManager class.
     * @param man A pointer to the ECS Manager.
     */
    AssetManager(Manager* man);

    /**
     * @brief Destructor for the AssetManager class.
     */
    ~AssetManager();

    /**
     * @brief Creates a projectile entity with specific properties.
     * @param pos The initial position of the projectile.
     * @param vel The velocity of the projectile.
     * @param range The maximum travel range of the projectile.
     * @param speed The speed at which the projectile moves.
     * @param id The unique identifier for the projectile texture.
     */
    void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

    /**
     * @brief Adds a texture to the asset manager's collection.
     * @param id The unique identifier for the texture.
     * @param path The file path to the texture image.
     */
    void AddTexture(std::string id, const char* path);

    /**
     * @brief Retrieves a texture from the asset manager.
     * @param id The unique identifier of the desired texture.
     * @return A pointer to the SDL_Texture associated with the provided id.
     */
    SDL_Texture* GetTexture(std::string id);

    /// A counter for tracking the number of projectiles created.
    static int projectileCounter;

private:
    Manager* manager; ///< A pointer to the ECS Manager.
    std::map<std::string, SDL_Texture*> textures; ///< A map of textures identified by their unique ids.
};
