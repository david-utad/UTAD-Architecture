/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once

class Input
{
public:

  enum EType
  {
    START_GAME,
    QUIT_GAME,
    PLAYER_MOVEMENT
  };

  Input(EType _eType, int _iKey, double _dValue = 0);
  virtual ~Input();

  /**
   * They return the parameters associated to the input.
   */
  EType GetType() const;
  int GetKey() const;
  double GetValue() const;

private:

  EType m_eType;
  int m_iKey;
  double m_dValue;
};