## Synopsis

This project is a Zork clone.

You are a pirate and your best treasure has been stolen. You have to recover it... and you know where to find the one that owns it right now. An epic battle awaits you, so be brave!

## Extra features

* **Prerequisites for exits**

...Some exits can only be used if the player owns specific items.

* **Real-time combat**

...There is a matrix that defines the battle map.

...The player is represented with 'P' and the enemy with 'E'.
...Each one has also its direction ('|', '_').

...The player can do the following actions: move, rotate, attack, projectile and heal.
...There is a simple AI for the enemy.

...The battle ends when one of the two has lost all its health points.

...The enemy items can only be taken if the player has won the battle.

## How to play

Commands represent player actions. Typing them (and their parameters, if needed) allow the user to control the player entity.

This is the list of commands:

**quit, q**
...Quits the game.

**commands, c**
...Displays all the commands.

**battle, b**
...Starts a battle. The player and the enemy must be in the same room.

**inventory, i**
...Displays all the items that the player owns.

**look, l ['me', _item_ or _enemy_]**
...Shows information about the specified entity. Parameters are optional. 'me' refers to the player itself. _item_ and _enemy_ are ingame names.

**go, g _direction_**
...The player goes to another room. _direction_ can be: 'n', 's', 'e', 'w', 'ne', 'nw', 'se' or 'sw'. 'north' and 'North' are valid too (and so on).

**take, t _item_**
...The player takes an item. The player and the item must be in the same room. The item must not be owned by the player. _item_ is an ingame name.

**drop, d _item_**
...The player drops an item. The item must be owned by the player. _item_ is an ingame name.

**place, p _item_ _item_**
...The player places an item inside another one. Both must be owned by the player. _item_ is an ingame name.

**(combat mode) attack, a _item_**
...The player attacks the enemy using the specified item. The item must be owned by the player. _item_ is an ingame name.

**(combat mode) projectile, pr _item_**
...The player throws the specified item to the enemy. The item must be owned by the player. The item is dropped. _item_ is an ingame name.

**(combat mode) heal, h _item_**
...The player heals using the specified item. The item must be owned by the player. _item_ is an ingame name.

**(combat mode) move, m _combatDirection_**
...The player moves in the specified direction. _combatDirection_ can be: 'u', 'd', 'l' or 'r'. 'up' and 'Up' are valid too (and so on).

**(combat mode) rotate, r _combatDirection_**
...The player rotates in the specified direction. _combatDirection_ can be: 'u', 'd', 'l' or 'r'. 'up' and 'Up' are valid too (and so on).

## How to win

* t Boat
* (optional) g n
...* (optional) t Sword
...* (optional) t Coconut
...* g s
* g s
* (optional) t Shell
* t Oar
* g ne
* t Sail
* g e
* b
* Win the battle. There is some rng here (hit/miss % of attack and projectile actions)
* t Treasure

## Link to Github

https://github.com/gerardpf2/Zork

## Author

Gerard Pros Figueras

## License

MIT License

Copyright (c) 2017 Gerard Pros Figueras

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.