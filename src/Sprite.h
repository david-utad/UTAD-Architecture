/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once
#include <string>
#include "Vec2.h"

class Sprite
{
public:

  Sprite();
  Sprite(const std::string& _sTFile);
  virtual ~Sprite();

  Sprite& operator=(const Sprite& _oOther);
  /**
   * It returns the image file url.
   */
  std::string GetUrl() const;
  /**
   * It returns the image sprite size.
   */
  Vec2 GetSize() const;
  /**
   * It returns a pointer to the generated image.
   */
  void* GetImage() const;

private:

  void* m_oImage;
  std::string m_sTFile;
};