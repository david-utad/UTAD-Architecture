/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once
#include <string>
#include <cstdint>

class RenderSystem
{
public:

  /**
   * @brief It draw all the entities in the current level.
   * @param _oScreen -> Screen where drawing the entities.
   * @param _bDebugDraw -> If active it will draw the colliders.
   */
  static void Render(void* _oScreen, bool _bDebugDraw = false);
  /**
   * It renders a text in the specified position in the screen.
   * @param _oScreen -> Screen where the text should be render.
   * @param _sText -> Text to show.
   * @param _vPosition -> Text position in the screen.
   * @param _uScale -> Text scale.
   */
   static void RenderText(void* _oScreen, const std::string& _sText, int _iX, int _iY, uint32_t _uScale);

private:

  /**
   * It renders the level map and background.
   * @param _oScreen -> Screen where drawing the entities.
   * @param _bDebugDraw -> If active it will draw the colliders.
   */
  static void RenderLevel(void* _oScreen, bool _bDebugDraw = false);
  /**
   * It renders the game UI.
   * @param _oScreen -> Screen where drawing the entities.
   * @param _bDebugDraw -> If active it will draw the colliders.
   */
  static void RenderUI(void* _oScreen, bool _bDebugDraw = false);
  /**
   * It render the colliders.
   * @param _oScreen -> Screen where drawing the entities. 
   * @param _uId -> entity id.
   * @param _iX -> horizontal position.
   * @param _iY -> vertical position.
   */
  static void RenderCollider(void* _oScreen, uint32_t _uId, int _iX, int _iY);
};