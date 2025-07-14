/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once
#include "ecs.hh"
#include "Vec2.h"
#include "Sprite.h"
#include "Enemy.h"
#include "AnimatedSprite.h"

/**
 * TPlayer struct is used to diferenciate the player from other entities
 */
struct TPlayer
{

};
/**
 * TUI struct is used to diferenciate UI component from other entities and store the scale.
 */
struct TUI
{
  uint32_t m_uScale;
};
/**
 * TTimer struct is used when to show the current time in the UI text components. 
 */
struct TTimer
{

};
/**
 * Available components in the game.
 */
using CPosition = component<Vec2, 1>;
using CVelocity = component<Vec2, 2>;
using CSprite = component<Sprite, 3>;
using CRCollider = component<Vec2, 4>;
using CCCollider = component<uint32_t, 5>;
using CPlayer = component<TPlayer, 6>;
using CEnemy = component<Enemy, 7>;
using CTile = component<uint32_t, 8>;
using CUI = component<TUI, 9>;
using CTimer = component<TTimer, 10>;
using CText = component<std::string, 11>;
using CAnimatedSprite = component<AnimatedSprite, 12>;