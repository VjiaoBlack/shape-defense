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
done, __future work__

* Game
  * Main Menu
  * Gameplay
    * Towers
      * Can build towers
      * __can repair towers__
      * __can destroy towers__
    * Resource system
      * Can have and spend resources
      * __can have buildings that modify resource usage / storage__
    * __Upgrade system__
    * Balancing
      * Has a few types of towers, one type of enemy
      * __More types of towers and enemies__
* Engine (very roughly an Entity-Component-System design)
  * Physics
    * efficient quadtree-based collision system
  * Graphics
    * Can render entities efficiently
    * __Can render entity types__
    * __Can move the camera around smoothly__
    * 
  * __Audio__
  * Basic AI
    * Enemies go towards closest player entity and will attack
    * __"heuristic grid" of best places to go towards, i.e. around walls__
  * __Advanced AI__
    * __Limited enemy view range__
    * __"Alive" enemies__
  * __I/O__
    * __serialization / deserialization__
  * UI
    * Have buttons, menus, etc.
    * Supports drawing from text files
    * __Easily supports drawing from images__
* Misc
  * __Write Wiki / Documentation__
  * __Plan out game design and engine design__
  * __write unit testing system__

### Known bugs:

* __no unit testing system__: whoops, this is pretty important actually
* __Quadtree__: sometimes, the quadtree system seems to "lose" elements, where 
  elements don't seem to be where we expect them to
* __entity lifetimes__: needs checking

