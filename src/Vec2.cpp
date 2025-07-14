#include "Vec2.h"
#include <cmath>

Vec2::Vec2() : m_dX(0), m_dY(0)
{

}

Vec2::Vec2(double _dX, double _dY) : m_dX(_dX), m_dY(_dY)
{

}

Vec2::Vec2(const Vec2& _oOther)
{
  m_dX = _oOther.GetX();
  m_dY = _oOther.GetY();
}

Vec2::~Vec2()
{

}

double Vec2::GetX() const
{
  return m_dX;
}

double Vec2::GetY() const
{
  return m_dY;
}

void Vec2::SetX(double _dX)
{
  m_dX = _dX;
}

void Vec2::SetY(double _dY)
{
  m_dY = _dY;
}

bool Vec2::operator==(const Vec2& _oOther) const
{
  return (m_dX == _oOther.GetX()) && (m_dY == _oOther.GetY());
}

bool Vec2::operator!=(const Vec2& _oOther) const
{
  return !operator==(_oOther);
}

Vec2& Vec2::operator=(const Vec2& _oOther)
{
  m_dX = _oOther.GetX();
  m_dY = _oOther.GetY();
  return *this;
}

Vec2 Vec2::operator+(const Vec2& _oOther) const
{
  return Vec2(m_dX + _oOther.GetX(), m_dY + _oOther.GetY());
}

Vec2& Vec2::operator+=(const Vec2& _oOther)
{
  m_dX += _oOther.GetX();
  m_dY += _oOther.GetY();
  return *this;
}

Vec2 Vec2::operator-(const Vec2& _oOther) const
{
  return Vec2(m_dX - _oOther.GetX(), m_dY - _oOther.GetY());
}

Vec2& Vec2::operator-=(const Vec2& _oOther)
{
  m_dX -= _oOther.GetX();
  m_dY -= _oOther.GetY();
  return *this;
}

double Vec2::Distance(const Vec2& _oOther) const
{
  return sqrt(((m_dX - _oOther.GetX()) * (m_dX - _oOther.GetX())) + ((m_dY - _oOther.GetY()) * (m_dY - _oOther.GetY())));
}