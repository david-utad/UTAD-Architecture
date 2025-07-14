/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once
#include "Sprite.h"
#include "Vec2.h"

class LevelSystem
{
public:

  /**
   * It inits the level with the size in the argument.
   * @param _iWidth -> level width.
   * @param _iHeight -> level size.
   */
  static void InitLevel(int _iWidth, int _iHeight);
  /**
   * It loads a map in the level. The level size will be changed by the map size.
   * @param _sFilename -> url to read the map (TMX file)
   * @param _sBackground -> url for the level background (optional)
   * @return 
   */
  static bool LoadLevel(const std::string& _sFilename, const std::string& _sBackground = "");
  /**
   * It returns the level size (map size if loaded).
   */
  static const Vec2& GetSize();
  /**
   * It returns the level tileset sprite.
   */
  static Sprite* GetTileset();
  /**
   * It returns the tile size.
   */
  static const Vec2& GetTileSize();
  /**
   * It returns the cols in the tileset.
   */
  static uint32_t GetTilesetCols();
  /**
   * It returns the level background sprite.
   */
  static Sprite* GetBackgorund();

private:

  /**
   * It concats the extracted path from the first argument with the second argument file name.
   * @param _sExtractPath -> file to extract the path.
   * @param _sFilename -> filename to add the extracted path.
   */
  static std::string ConcatPathToFile(const std::string& _sExtractPath, const std::string& _sFilename);

  static Sprite* oBackground, *oTileset;
  static Vec2 vLevelSize, vTileSize;
  static uint32_t uTilesetCols;
};