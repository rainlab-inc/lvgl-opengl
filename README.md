# lvgl-opengl

## Draw Functions
### Rectangle
- draw_shadow 
- draw_bg
    * plain rect :white_check_mark:
    * radius mask :white_check_mark:
      * TODO: more efficient corner rendering (Use same buffer for all 9 pieces per rectangle.)
      * TODO: do antialiasing with respect to radius, not with an arbitrary constant,
    * TODO: other masks? gradients?
- draw_bg_img
    * maybe call draw_img with rect borders?
- draw_border
- draw_outline
### Image
- draw_img :white_check_mark:
  * TODO: hash textures, avoid creating same textures if they are used more than once.
  * TODO: handle recolor operation more wisely
  * TODO: handle masks
### Letter
TODO: Look how lvgl handles glyphs.
Presumably, it will be easy if we figure out texture hashing for each glyph.

## Rare Draw Functions 
### Arc
TODO: Look for how to draw efficient arcs with GL.
### Line
TODO: It will be probably easy - efficient if we draw with shaders.
### Polygon
TODO: Look which components use draw polygon.
