# Shape Defense
Shape Defense is a top-down tower-defense-based game written solely with C++ 
and SDL2. It's partly an exercise in game engine architecture design; partly an exercise in optimization; and partly an exercise in game construction :)

Feel free to contribute; just send me a message (preferably), or a pull request directly.

### Dependencies List:
* C++17
* SDL2
  * SDL_Image
  * SDL_TTF
* CMake

### Tools Used:
* valgrind
* gdb
* CLion
* CMake
* gnuprof

### Feature List:
done, [n] __future work__

* Game
  * Main Menu
  * Gameplay
    * Towers
      * Can build towers
      * [n] __can repair towers__
      * [n] __can destroy towers__
    * Resource system
      * Can have and spend resources
      * [n] __can have buildings that modify resource usage / storage__
    * [n] __Upgrade system__
    * Balancing
      * Has a few types of towers, one type of enemy
      * [n] __More types of towers and enemies__
* Engine (very roughly an Entity-Component-System design)
  * Physics
    * efficient quadtree-based collision system
  * Graphics
    * Can render entities efficiently
    * [n] __Can render entity types__
    * [n] __Can move the camera around smoothly__
    * 
  * [n] __Audio__
  * Basic AI
    * Enemies go towards closest player entity and will attack
    * [n] __"heuristic grid" of best places to go towards, i.e. around walls__
  * [n] __Advanced AI__
    * [n] __Limited enemy view range__
    * [n] __"Alive" enemies__
  * [n] __I/O__
    * [n] __serialization / deserialization__
  * UI
    * Have buttons, menus, etc.
    * Supports drawing from text files
    * [n] __Easily supports drawing from images__
* Misc
  * [n] __Write Wiki / Documentation__
  * [n] __Plan out game design and engine design__
  * [n] __write unit testing system__

### Known bugs:

* [n] __no unit testing system__: whoops, this is pretty important actually
* [n] __Quadtree__: sometimes, the quadtree system seems to "lose" elements, where 
  elements don't seem to be where we expect them to
* [n] __entity lifetimes__: needs checking

