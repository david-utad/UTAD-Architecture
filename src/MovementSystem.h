/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once

class MovementSystem
{
public:

  /**
   * @brief It moves the entities in the current level.
   * @param _dDeltatime -> Time to update.
   */
  static void Update(double _dDeltatime);
};