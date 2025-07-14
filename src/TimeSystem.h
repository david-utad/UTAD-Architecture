/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once

class TimeSystem
{
public:

  /**
   * It returns the time in the game since it started.
   */
  static double GetGameTime();
  /**
   * It restart the time in the game to 0.
   */
  static void RestartTime();
  /**
   * It updates the time in the game.
   * @param _dDeltatime -> time to update.
   */
  static void Update(double _dDeltatime);

private:

  static double dGameTime;
};

