/*  
 * font.h
 * 
 * This header file defines the system font for an 8x8 pixel character set.
 * It provides font bitmap data and macros for accessing glyphs.
 * 
 * Author: Andres Isturiz, Tameem Aboueldahab  
 * Date: 28/02/25  
 */  

 #ifndef FONT_H
 #define FONT_H
 
 #include "raster.h"

 extern const UINT8 font[];
 
 #define FONT_HEIGHT 8
 #define FONT_WIDTH 8
 #define CHAR_BEL    7
 #define CHAR_TAB    9
 #define CHAR_LF    10
 #define CHAR_VT    11
 #define CHAR_FF    12
 #define CHAR_CR    13
 #define CHAR_DEL  127
 
 /* Macro to determine if a character is printable */
 #define IS_PRINTABLE(i) ((i) >= ' ' && (i) <= '~')
 
 /* Macro to get the glyph start position in the font array */
 #define GLYPH_START(i) (font + (((i) - ' ') << 3))
 
 #endif
 