#include "Input.h"

Input::Input(EType _eType, int _iKey, double _dValue) :
  m_eType(_eType),
  m_iKey(_iKey),
  m_dValue(_dValue)
{

}

Input::~Input()
{

}

Input::EType Input::GetType() const
{
  return m_eType;
}

int Input::GetKey() const
{
  return m_iKey;
}

double Input::GetValue() const
{
  return m_dValue;
}