#include "Sprite.h"
#include "tigr.h"

Sprite::Sprite() : 
  m_oImage(nullptr),
  m_sTFile("")
{

}

Sprite::Sprite(const std::string& _sTFile) : 
  m_sTFile(_sTFile)
{
  m_oImage = tigrLoadImage(_sTFile.c_str());
}

Sprite::~Sprite()
{
  if (m_oImage != nullptr)
  {
    Tigr* oTImage = static_cast<Tigr*>(m_oImage);
    tigrFree(oTImage);
    m_oImage = nullptr;
  }
}

Sprite& Sprite::operator=(const Sprite& _oOther)
{
  m_oImage = tigrLoadImage(_oOther.GetUrl().c_str());
  m_sTFile = _oOther.GetUrl();
  return *this;
}

std::string Sprite::GetUrl() const
{
  return m_sTFile;
}

Vec2 Sprite::GetSize() const
{
  Tigr* oTImage = static_cast<Tigr*>(m_oImage);
  return Vec2(oTImage->w, oTImage->h);
}

void* Sprite::GetImage() const
{
  return m_oImage;
}