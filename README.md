# Pang Game Documentation

The final exercise for the Architecture class.

## Overview

The game is bassed in the pattern Entity Component System.
The entities are loaded from /data/gamedata.xml.
The amp is created with Tiled application (www.mapeditor.org) and a texture for the background. It is located in /data/pang_map.tmx. The map tiles has a rectangle collision, but if the map is removed, the enemies will collide with the window limits.
The Hi-score is saved in the file /save_data/hiscore.xml.
The default inputs to move the player are `A`, `D`, `<-` and `->`, but it could be added any new input in the game.
The start and end game texts could be modified.
The enemy spawner is configured with 9 enemy types: 3 colors and 3 different sizes. Each enemy has a different horizontal velocity and bounce force.
The player has movement animations.
There is a sound feedback when the enemies collide.

## The Game

The player should evade all the enemies. When an enemy collides with the player, the game will end.