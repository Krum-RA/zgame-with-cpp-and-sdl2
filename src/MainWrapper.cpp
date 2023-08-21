#include "MainWrapper.h"

/**
 * @file MainWrapper.h
 * @brief Contains the function to run the main game loop.
 */

 /**
  * @brief Runs the main game loop.
  * @param game A reference to the Game instance.
  *
  * This function initializes the game window, enters the main loop, and manages
  * the game loop timing and events. The loop handles events, updates the game
  * state, and renders the scene. The loop maintains a constant frame rate by
  * delaying when necessary.
  *
  * @note This function assumes that the Game instance has been initialized
  *       using the `init` function and cleaned up using the `clean` function.
  *
  * @param game The initialized Game instance that will be used in the loop.
  */
void RunGameLoop(Game& game)
{
    const int FPS = 60; ///< The desired frames per second for the game loop.
    const int frameDelay = 1000 / FPS; ///< The delay between frames in milliseconds.

    Uint32 frameStart; ///< The timestamp at the start of a frame.
    int frameTime; ///< The time taken to process a frame.

    // Initialize the game window
    game.init("Game engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    // Main game loop
    while (game.running())
    {
        frameStart = SDL_GetTicks(); ///< Record the start time of the frame.

        // Handle events, update game state, and render scene
        game.handleEvents();
        game.update();
        game.render();

        frameTime = SDL_GetTicks() - frameStart; ///< Calculate the time taken for this frame.

        // Delay to maintain the desired frame rate
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // Clean up resources before exiting
    game.clean();
}
