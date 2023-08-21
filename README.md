# zgame-with-cpp-and-sdl2
This is my attempt to make a game with cpp and sdl2. 
The game is currently unfinished and I plan to improve it further in the future.
# Building the game
All you have to do to build the game is clone or download the repo once done either open the repo with visual studio and let the cmakelists generation finished.
After that you should be able to run the main1 exe in debug mode but I recommend to build in release mode as the animations and collision don't work in debug mode.
As a side note if you build in release and the animations don't work delete the cache and reconfigure
# Running the tests
In order to run the tests you will have to download the latest release of unittest.cpp which you can do from the link here: https://github.com/unittest-cpp/unittest-cpp
After that follow the steps in the wiki to build the project with cmake
Once done all you will have to do is uncomment the commands after the "Find UnitTest++ library" in the cmakelists.txt of the game project.
# Generating the documentation
Only the most basic parts of the project have been documented using doxygen. All the other undocumented parts are pretty much self explanatory but I will document them in the future.
# Playing the Game
The character is controlled with the the W,A,S,D keys. You can shoot projectiles with the E button and each deals 10 damage to the zombie.
You can also revive your player if you die with the J button.
The zombie deals 30 damage to the player with each bite and can be revived with the K button if it dies. The zombie also has a patrol chase and attack states and will remain in patrol mode unitil the player gets close to the zombie.
# Hope you enjoy :)
