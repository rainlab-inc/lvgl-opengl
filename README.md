# lvgl-opengl

This is an example SDL application for OpenGL ES 2.0 implementation for [LVGL](https://github.com/lvgl/lvgl) aimed for to run on PinePhone. 

OpenGL ES 2.0 fork of the LVGL can be found [here](https://github.com/rainlab-inc/lvgl).

SDL Driver can be found [here](https://github.com/rainlab-inc/lv_drivers).

## Screenshot
![screenshot](screenshot.png)

## Quick Start

### Requirements
* OpenGL ES >= 2.0
* cmake
* SDL2
* libepoxy

### Cloning the repository
``` console
$ git clone https://github.com/rainlab-inc/lvgl-opengl
$ cd lvgl-opengl
$ git submodule update --init --remote --recursive
```

### Building 
#### CMake
``` console
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
$ ./lvgl-opengl
```

## Draw Functions
### Rectangle
- draw_shadow 
- draw_bg
    * plain rect :white_check_mark:
    * radius mask :white_check_mark:
      * **TODO**: more efficient corner rendering (Use same buffer for all 9 pieces per rectangle.)
      * **TODO**: do antialiasing with respect to radius, not with an arbitrary constant,
    * **TODO**: other masks? gradients?
- draw_bg_img
    * maybe call draw_img with rect borders?
- draw_border
- draw_outline
### Image
- Hash textures with LRU cache :white_check_mark:
- draw_img :white_check_mark:
  * **TODO**: hash textures, avoid creating same textures if they are used more than once. :white_check_mark:
  * **TODO**: handle recolor operation more wisely
  * **TODO**: handle masks
### Letter
- Hash glyphs with LRU cache :white_check_mark:
- **TODO**: Look for pixel perfect alignment for glitches.
- **TODO**: Test for CJK characters.
- **TODO**: Pack glyphs to efficient rendering.

### Arc
**TODO**: Look for how to draw efficient arcs with GL.
### Line
**TODO**: It will be probably easy - efficient if we draw with shaders.
### Polygon
**TODO**: Look which components use draw polygon.
