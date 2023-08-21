#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "ECS.h"
#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;

/**
 * @class Game
 * @brief Represents the main game class responsible for managing game loop and resources.
 */
class Game
{
public:
    /**
     * @brief Constructor for the Game class.
     */
    Game();

    /**
     * @brief Destructor for the Game class.
     */
    ~Game();

    /**
     * @brief Initializes the game window and resources.
     * @param title The title of the game window.
     * @param xposition The initial x-coordinate of the game window.
     * @param yposition The initial y-coordinate of the game window.
     * @param width The width of the game window.
     * @param height The height of the game window.
     * @param fullscreen Set to `true` to enable fullscreen mode, `false` otherwise.
     */
    void init(const char* title, int xposition, int yposition, int width, int height, bool fullscreen);

    /**
     * @brief Handles events (user input) in the game.
     * This function is called within the main game loop to handle events such as
     * keyboard and mouse input.
     */
    void handleEvents();

    /**
     * @brief Updates the game state.
     * This function is called within the main game loop to update the game logic
     * and entities.
     */
    void update();

    /**
     * @brief Renders the game scene.
     * This function is called within the main game loop to render the visual
     * elements of the game.
     */
    void render();

    /**
     * @brief Cleans up resources before exiting the game.
     * This function is responsible for releasing any allocated memory and
     * cleaning up resources used by the game.
     */
    void clean();

    /**
     * @brief Checks if the game is currently running.
     * @return `true` if the game is running, `false` otherwise.
     */
    bool running() { return isRunning; }

    /**
     * @brief Initializes player and enemy entities.
     * @param player The player entity.
     * @param enemy The enemy entity.
     */
    void initCreatures(Entity& player, Entity& enemy);

    /// Static members shared among instances of the Game class.
    static SDL_Renderer* renderer; ///< The SDL renderer used for rendering graphics.
    static SDL_Event event; ///< The SDL event used to handle input events.
    static bool isRunning; ///< Indicates whether the game loop is running.
    static SDL_Rect camera; ///< The camera's position and dimensions for scrolling.
    static AssetManager* assets; ///< The asset manager for managing game assets.

    /**
     * @brief Enumerated labels for entity groups.
     * These labels help categorize entities within the ECS.
     */
    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayers,
        groupEnemies,
        groupColliders,
        groupProjectiles
    };

private:
    int cntr = 0; ///< A counter variable for internal use.
    SDL_Window* window; ///< The SDL window used for displaying the game.
};
