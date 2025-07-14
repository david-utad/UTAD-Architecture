/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once

class Vec2
{
public:

  Vec2();
  Vec2(double _dX, double _dY);
  Vec2(const Vec2& _oOther);
  virtual ~Vec2();
  /**
   * Getters for X and Y parameters.
   */
  double GetX() const;
  double GetY() const;
  /**
   * Setters for X and Y parameters.
   */
  void SetX(double _dX);
  void SetY(double _dY);
  /**
   * Compare operators with other Vec2.
   */
  bool operator==(const Vec2& _oOther) const;
  bool operator!=(const Vec2& _oOther) const;
  /**
   * Addition and subtract operators with other Vec2.
   */
  Vec2& operator=(const Vec2& _oOther);
  Vec2 operator+(const Vec2& _oOther) const;
  Vec2& operator+=(const Vec2& _oOther);
  Vec2 operator-(const Vec2& _oOther) const;
  Vec2& operator-=(const Vec2& _oOther);
  /**
   * It returns the distance between the current Vec2 to _oOther.
   */
  double Distance(const Vec2& _oOther) const;

private:

  double m_dX, m_dY;
};