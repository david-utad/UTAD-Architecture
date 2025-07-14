#include "LevelSystem.h"
#include "pugixml.hpp"
#include "EntityManager.h"

Sprite* LevelSystem::oBackground = nullptr;
Sprite* LevelSystem::oTileset = nullptr;
Vec2 LevelSystem::vLevelSize = Vec2();
Vec2 LevelSystem::vTileSize = Vec2();
uint32_t LevelSystem::uTilesetCols = 0;

void LevelSystem::InitLevel(int _iWidth, int _iHeight)
{
  vLevelSize = Vec2(_iWidth, _iHeight);
}

bool LevelSystem::LoadLevel(const std::string& _sFilename, const std::string& _sBackground)
{
  if (!_sBackground.empty())
  {
    oBackground = new Sprite(_sBackground.c_str());
  }
  pugi::xml_document xmlDoc;
  pugi::xml_parse_result xmlParseResult = xmlDoc.load_file(_sFilename.c_str());
  if (xmlParseResult)
  {
    pugi::xml_node mapNode = xmlDoc.child("map");
    vTileSize = Vec2(mapNode.attribute("tilewidth").as_int(), mapNode.attribute("tileheight").as_int());
    vLevelSize = Vec2(mapNode.attribute("width").as_int() * vTileSize.GetX(), mapNode.attribute("height").as_int() * vTileSize.GetY());
    pugi::xml_node tilesetNode = mapNode.child("tileset");
    // Map texture
    pugi::xml_node imageNode = tilesetNode.child("image");
    std::string sTextureFile = ConcatPathToFile(_sFilename, imageNode.attribute("source").as_string());
    oTileset = new Sprite(sTextureFile.c_str());
    uTilesetCols = tilesetNode.attribute("columns").as_uint();
    // Tile map
    uint32_t uFirstTileId = tilesetNode.attribute("firstgid").as_uint();
    uint32_t uCols = mapNode.child("layer").attribute("width").as_uint();
    uint32_t uIndex = 0;
    pugi::xml_node tileNode = mapNode.child("layer").child("data").child("tile");
    while (tileNode)
    {
      uint32_t uTileId = tileNode.attribute("gid").as_uint();
      if (uTileId >= uFirstTileId)
      {
        Vec2 oTilePos(vTileSize.GetX() * (uIndex % uCols), vTileSize.GetY() * (uIndex / uCols));
        EntityManager::GetInstance()->CreateTileEntity(uTileId - uFirstTileId, oTilePos, vTileSize);
      }
      tileNode = tileNode.next_sibling("tile");
      uIndex++;
    }
  }
  return xmlParseResult;
}

const Vec2& LevelSystem::GetSize()
{
  return vLevelSize;
}

Sprite* LevelSystem::GetTileset()
{
  return oTileset;
}

const Vec2& LevelSystem::GetTileSize()
{
  return vTileSize;
}

uint32_t LevelSystem::GetTilesetCols()
{
  return uTilesetCols;
}

Sprite* LevelSystem::GetBackgorund()
{
  return oBackground;
}

std::string LevelSystem::ConcatPathToFile(const std::string& _sExtractPath, const std::string& _sFilename)
{
  std::string sFilePath = _sExtractPath;
  while (sFilePath.find("\\") != std::string::npos)
  {
    sFilePath.replace(sFilePath.find("\\"), 1, "/");
  }
  sFilePath = sFilePath.substr(0, sFilePath.rfind('/'));
  if (sFilePath.size() > 0)
  {
    sFilePath += "/" + _sFilename;
  }
  return sFilePath;
}