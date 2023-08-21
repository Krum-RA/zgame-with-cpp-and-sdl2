/**
 * @file main.cpp
 * @brief Entry point for the game application.
 */

#include "MainWrapper.h"

 /// A pointer to the game instance.
Game* game = nullptr;

/**
 * @brief The main function of the application.
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return An integer indicating the exit status of the application.
 *
 * This function initializes the game instance, runs the game loop,
 * and then cleans up the resources before exiting.
 */
int main(int argc, char* argv[]) 
{
    // Create a new game instance

    game = new Game();
    // Run the main game loop
    RunGameLoop(*game);

    return 0;
}
