#include "RenderSystem.h"
#include <sstream>
#include "tigr.h"
#include "Components.h"
#include "TimeSystem.h"
#include "LevelSystem.h"

void RenderSystem::Render(void* _oScreen, bool _bDebugDraw)
{
  Tigr* oTScreen = static_cast<Tigr*>(_oScreen);
  // Map and background to show in the game.
  RenderLevel(_oScreen, _bDebugDraw);
  // Entities without animations to draw in the game
  for (uint32_t uId : join<CPosition, CSprite>())
  {
    Vec2& vPosition = get<CPosition>(uId);
    Sprite& oSprite = get<CSprite>(uId);
    Tigr* oTImage = static_cast<Tigr*>(oSprite.GetImage());
    tigrBlitAlpha(oTScreen, oTImage, static_cast<int>(vPosition.GetX()), static_cast<int>(vPosition.GetY()), 0, 0, oTImage->w, oTImage->h, 1.f);
    if (_bDebugDraw)
    {
      RenderCollider(_oScreen, uId, static_cast<int>(vPosition.GetX()), static_cast<int>(vPosition.GetY()));
    }
  }
  // Entities with animations to draw in the game
  for (uint32_t uId : join<CPosition, CAnimatedSprite>())
  {
    Vec2& vPosition = get<CPosition>(uId);
    AnimatedSprite& oAnimatedSprite = get<CAnimatedSprite>(uId);
    Tigr* oTImage = static_cast<Tigr*>(oAnimatedSprite.GetCurrentImage());
    uint32_t uFrames = oAnimatedSprite.GetCurrentImageFrames();
    int iWidth = oTImage->w / uFrames;
    int iX = (static_cast<int>(oAnimatedSprite.GetCurrentFrame()) % uFrames) * iWidth;
    tigrBlitAlpha(oTScreen, oTImage, static_cast<int>(vPosition.GetX()), static_cast<int>(vPosition.GetY()), iX, 0, iWidth, oTImage->h, 1.f);
    if (_bDebugDraw)
    {
      RenderCollider(_oScreen, uId, static_cast<int>(vPosition.GetX()), static_cast<int>(vPosition.GetY()));
    }
  }
  // UI components to show in the game.
  RenderUI(_oScreen, _bDebugDraw);
}

void RenderSystem::RenderText(void* _oScreen, const std::string& _sText, int _iX, int _iY, uint32_t _uScale)
{
  // Tigr don't support to scale text, then it is necessary to scale it manually.
  Tigr* oTScreen = static_cast<Tigr*>(_oScreen);
  int iWidth = tigrTextWidth(tfont, _sText.c_str());
  int iHeight = tigrTextHeight(tfont, _sText.c_str());
  Tigr* oTextCanvas = tigrBitmap(iWidth, iHeight);
  tigrPrint(oTextCanvas, tfont, 0, 0, tigrRGB(0xFF, 0xFF, 0xFF), _sText.c_str());
  for (int iY = 0; iY < oTextCanvas->h; ++iY)
  {
    for (int iX = 0; iX < oTextCanvas->w; ++iX)
    {
      TPixel pixel = tigrGet(oTextCanvas, iX, iY);
      if (pixel.a == 0)
      {
        continue;
      }
      for (uint32_t uScaledY = 0; uScaledY < _uScale; ++uScaledY)
      {
        for (uint32_t uScaledX = 0; uScaledX < _uScale; ++uScaledX)
        {
          int iXPosition = static_cast<int>(_iX + iX * _uScale + uScaledX);
          int iYPosition = static_cast<int>(_iY + iY * _uScale + uScaledY);
          tigrPlot(oTScreen, iXPosition, iYPosition, pixel);
        }
      }
    }
  }
  tigrFree(oTextCanvas);
}

void RenderSystem::RenderLevel(void* _oScreen, bool _bDebugDraw)
{
  Tigr* oTScreen = static_cast<Tigr*>(_oScreen);
  Sprite* oTileset = LevelSystem::GetTileset();
  Sprite* oBackground = LevelSystem::GetBackgorund();
  if (oBackground != nullptr)
  {
    const Vec2& vSize = LevelSystem::GetSize();
    tigrBlit(oTScreen, static_cast<Tigr*>(oBackground->GetImage()), 0, 0, 0, 0, static_cast<int>(vSize.GetX()), static_cast<int>(vSize.GetY()));
  }
  if (oTileset != nullptr)
  {
    const Vec2& vTileSize = LevelSystem::GetTileSize();
    uint32_t uTilesetCols = LevelSystem::GetTilesetCols();
    for (uint32_t uId : join<CTile, CPosition>())
    {
      uint32_t uTileId = get<CTile>(uId);
      Vec2& vPosition = get<CPosition>(uId);
      int iX = (uTileId % uTilesetCols) * static_cast<int>(vTileSize.GetX());
      int iY = (uTileId / uTilesetCols) * static_cast<int>(vTileSize.GetY());
      tigrBlit(oTScreen, static_cast<Tigr*>(oTileset->GetImage()), static_cast<int>(vPosition.GetX()), static_cast<int>(vPosition.GetY()),
        iX, iY, static_cast<int>(vTileSize.GetX()), static_cast<int>(vTileSize.GetY()));
      if (_bDebugDraw)
      {
        RenderCollider(_oScreen, uId, static_cast<int>(vPosition.GetX()), static_cast<int>(vPosition.GetY()));
      }
    }
  }
}

void RenderSystem::RenderUI(void* _oScreen, bool _bDebugDraw)
{
  for (uint32_t uId : join<CUI, CText, CPosition>())
  {
    Vec2& vPosition = get<CPosition>(uId);
    std::string sText = get<CText>(uId);
    if (has<CTimer>(uId))
    {
      std::ostringstream sTimer;
      sTimer.precision(2);
      sTimer << std::fixed << TimeSystem::GetGameTime();
      sText.append(sTimer.str());
    }
    TUI tUI = get<CUI>(uId);
    RenderText(_oScreen, sText, static_cast<int>(vPosition.GetX()), static_cast<int>(vPosition.GetY()), tUI.m_uScale);
  }
}

void RenderSystem::RenderCollider(void* _oScreen, uint32_t _uId, int _iX, int _iY)
{
  if (has<CCCollider>(_uId))
  {
    uint32_t oCollider = get<CCCollider>(_uId);
    tigrCircle(static_cast<Tigr*>(_oScreen), _iX + oCollider, _iY + oCollider, oCollider, tigrRGB(0xFF, 0, 0));
  }
  else if (has<CRCollider>(_uId))
  {
    Vec2& vCollider = get<CRCollider>(_uId);
    tigrRect(static_cast<Tigr*>(_oScreen), _iX, _iY, static_cast<int>(vCollider.GetX()), static_cast<int>(vCollider.GetY()), tigrRGB(0xFF, 0, 0));
  }
}