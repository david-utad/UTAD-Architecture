#include "TimeSystem.h"

double TimeSystem::dGameTime = 0;

double TimeSystem::GetGameTime()
{
    return dGameTime;
}

void TimeSystem::RestartTime()
{
  dGameTime = 0;
}

void TimeSystem::Update(double _dDeltaTime)
{
  dGameTime += _dDeltaTime;
}