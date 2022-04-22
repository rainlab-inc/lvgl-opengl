# lvgl-opengl
This is an example SDL application for OpenGL ES 2.0 implementation for [LVGL](https://github.com/lvgl/lvgl) aimed for to run on PinePhone. 

OpenGL ES 2.0 fork of the LVGL can be found [here](https://github.com/rainlab-inc/lvgl).

SDL Driver can be found [here](https://github.com/rainlab-inc/lv_drivers).

## Quick Start
### CMake
``` console
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
$ ./lvgl-opengl
```

## Draw Functions
### Rectangle
**TODO**: Coordinates are handled wrong. Need to calculate properly especially for the rounded rectangle.
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
**TODO**: Unable to render images in Release mode. ("No data" error)
- draw_img :white_check_mark:
  * **TODO**: hash textures, avoid creating same textures if they are used more than once. :white_check_mark:
  * **TODO**: handle recolor operation more wisely
  * **TODO**: handle masks
### Letter
- **TODO**: Look for pixel perfect alignment for glitches.
- **TODO**: Test for CJK characters.

### Arc
**TODO**: Look for how to draw efficient arcs with GL.
### Line
**TODO**: It will be probably easy - efficient if we draw with shaders.
### Polygon
**TODO**: Look which components use draw polygon.
