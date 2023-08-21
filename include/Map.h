#pragma once
#include <string>

/**
 * @class Map
 * @brief Represents a map in the game world.
 */
class Map
{
public:
    /**
     * @brief Constructor for the Map class.
     * @param tID The ID of the map's texture.
     * @param mapscale The scale of the map.
     * @param tilesize The size of each tile.
     */
    Map(std::string tID, int mapscale, int tilesize);

    /**
     * @brief Destructor for the Map class.
     */
    ~Map();

    /**
     * @brief Loads a map from a file.
     * @param path The path to the map file.
     * @param sizeX The width of the map in tiles.
     * @param sizeY The height of the map in tiles.
     */
    void LoadMap(std::string path, int sizeX, int sizeY);

    /**
     * @brief Adds a tile to the map.
     * @param srcX The source x-coordinate of the tile image.
     * @param srcY The source y-coordinate of the tile image.
     * @param xpos The x-coordinate of the tile's position.
     * @param ypos The y-coordinate of the tile's position.
     */
    void AddTile(int srcX, int srcY, int xpos, int ypos);

    /**
     * @brief Loads tile images from a file.
     * @param path The path to the tile image file.
     * @param sizeX The width of the tile image in pixels.
     * @param sizeY The height of the tile image in pixels.
     */
    void LoadTiles(std::string path, int sizeX, int sizeY);

    /**
     * @brief Loads colliders for the map from a file.
     * @param path The path to the collider data file.
     * @param sizeX The width of the collider map in tiles.
     * @param sizeY The height of the collider map in tiles.
     */
    void LoadColliders(std::string path, int sizeX, int sizeY);

    /**
     * @brief Retrieves the size of each tile.
     * @return The size of each tile in pixels.
     */
    int GetTileSize();

private:
    std::string texID; ///< The ID of the map's texture.
    int mscale; ///< The scale of the map.
    int tsize; ///< The size of each tile.
    int scaledsize; ///< The scaled size of each tile.
};
