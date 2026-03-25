/*  
 * RASTER.C
 * 
 * This file implements raster-based graphics functions for the Atari ST.
 * It includes functions for drawing pixels, lines, bitmaps, and rendering text.
 * 
 * Author: Tameem Aboueldahab, Andres Isturiz  
 * Date: 28/02/25  
 */
#include "raster.h"
#include "font.h"
#define TOTAL_LONGWORDS 8000;


#define VIDEO_BASE_HIGH  ((volatile UINT8 *)0xFFFF8201)
#define VIDEO_BASE_MID   ((volatile UINT8 *)0xFFFF8203)

extern void set_video_base_asm(UINT32 address);

/*
 * Clears the entire screen by setting all pixels to zero.
 * 
 * Parameters:
 * - base: Pointer to the screen buffer.
 */
void clear_screen(UINT32 *base) {
    UINT32 *start = base;
    UINT32 clear = 0x00000000;
    int i;
    for (i = 0; i < SCREEN_SZ_LONG; i++) {
        *start++ = clear;
    }
}
/*
 * Plots a pixel on the screen at the given coordinates.
 * 
 * Parameters:
 * - base: Pointer to the screen buffer.
 * - row: Row coordinate (y-axis).
 * - col: Column coordinate (x-axis).
 */
void plot_pixel(UINT8 *base, int row, int col) {
    if (col >= 0 && col < SCREEN_WIDTH && row >= 0 && row < SCREEN_HEIGHT)
    *(base + row * 80 + (col >> 3)) |= 1 << (7 - (col & 7));
    }


/*
 * Draws a horizontal line between two points at a specified y-coordinate.
 * 
 * Parameters:
 * - base: Pointer to the screen buffer.
 * - x1: Starting x-coordinate.
 * - x2: Ending x-coordinate.
 * - y: Y-coordinate.
 */
void plot_hline(UINT8 *base, int x1, int x2, int y) {
    int byte_start, byte_end, bit_offset_start, bit_offset_end, temp, i;
    UINT8 *addr;
    /* Ensure the y-coordinate is within screen bounds and x1, x2 are within valid range */
    if (y < 0 || y >= SCREEN_HEIGHT || x1 >= SCREEN_WIDTH || x2 < 0)
        return; 

    if (x1 > x2) {  
        temp = x1;
        x1 = x2;
        x2 = temp;
    }
    /* Compute the byte positions in memory */
    byte_start = x1 >> 3;   
    byte_end = x2 >> 3;     
    bit_offset_start = x1 & 7; 
    bit_offset_end = x2 & 7;  
    addr = base + (y * 80) + byte_start;

    /* Case 1: If x1 and x2 are aligned to full byte boundaries */
    if (bit_offset_start == 0 && bit_offset_end == 7) {
        for (i = byte_start; i <= byte_end; i++) {
            *addr++ = 0xFF;
        }
        return;
    }
    /* Case 2: General case where x1 and/or x2 are not byte-aligned */
    *addr |= 0xFF >> bit_offset_start;
    addr++;
    
    for (i = byte_start + 1; i < byte_end; i++) {
        *addr++ = 0xFF;
    }
    *addr |= 0xFF << (7 - bit_offset_end);
}

/*
 * Draws a vertical line from (x, y1) to (x, y2).
 * 
 * Parameters:
 * - base: Pointer to the screen buffer.
 * - x: X-coordinate.
 * - y1: Starting Y-coordinate.
 * - y2: Ending Y-coordinate.
 */
void plot_vline(UINT8 *base, int x, int y1, int y2) {
    int i;
    UINT8 *p_start_address;
    int bit_position;
    int swap;

    if (x < 0 || x >= SCREEN_WIDTH || y1 < 0 || y2 >= SCREEN_HEIGHT - 1) {
        return;
    }
    if (y1 > y2) {
        swap = y1;
        y1 = y2;
        y2 = swap;
    }
    p_start_address = base + (y1 * 80) + (x >> 3); 
    bit_position = (7 - (x & 7));
    
    for (i = y1; i <= y2; i++) {
        *p_start_address |= (1 << bit_position);
        p_start_address += 80;
    }
    return;
}


/*
 * Draws a bitmap at a specified position.
 * 
 * Parameters:
 * - base: Pointer to the screen buffer.
 * - row: Starting row position (y-axis).
 * - col: Starting column position (x-axis).
 * - bitmap: Pointer to the bitmap data.
 * - height: Height of the bitmap.
 */
void plot_bitmap_16(UINT16 *base, int row, int col, const UINT16 *bitmap, unsigned int height) {
    int i;
    UINT16 *start;
    if (row < 0 || row + height > SCREEN_HEIGHT || col < 0 || col >= SCREEN_WIDTH) 
        return;

    start = base + (row * 40) + (col >> 4);
    for ( i = 0; i < height; i++) {
        *start |= bitmap[i];
        start += 40; 
    }
    return;
}

/*
 * Draws a general line using Bresenham's algorithm.
 * 
 * Parameters:
 * - base: Pointer to the screen buffer.
 * - x0, y0: Starting coordinates.
 * - x1, y1: Ending coordinates.
 */
void plot_gline(UINT8 *base, int x0, int y0, int x1, int y1) {
    int e2;
    int dx, dy, sx, sy, err;

    if (x1 > x0) {
        dx = x1 - x0; 
        sx = 1;
    } 
        else {
            dx = x0 - x1;       
            sx = -1;
        }

    if (y1 > y0) {
        dy = y1 - y0; 
        sy = 1; 
    } 
        else {
            dy = y0 - y1; 
            sy = -1; 
        }

    err = dx - dy;

    for (;;) {
        plot_pixel(base, x0, y0);

    /* Terminate if we've reached the endpoint*/
        if (x0 == x1 && y0 == y1) {
            break;
        }

        e2 = 2 * err;

    /* Decide whether to move in the x-direction */
        if (e2 > -dy) { 
            err -= dy;
            x0 += sx;
        }

    /* Decide whether to move in the y-direction*/
        if (e2 < dx) { 
            err += dx;
            y0 += sy;
        }
    }
}



/*
 * Renders a text string onto the screen.
 * 
 * Parameters:
 * - base: Pointer to the screen buffer.
 * - x: X-coordinate.
 * - y: Y-coordinate.
 * - text: Pointer to the string to be rendered.
 */
void plot_text(UINT16 *base, int x, int y, const char *text) {
    const UINT8 *bitmap;
    UINT8 font_row;
    UINT16 *addr;
    int bit_offset, row;
    while (*text) {

        if (*text == CHAR_LF) {
            y += FONT_HEIGHT;
            x = 0;
        } else if (*text == CHAR_CR) {
            x = 0;
        } else if (IS_PRINTABLE(*text)) {  
            bitmap = GLYPH_START(*text);
            addr = base + (y * 40) + (x >> 4);
            bit_offset = x & 15;

            /* Render the character row by row */
            for (row = 0; row < FONT_HEIGHT; row++) {
                font_row = bitmap[row];

                /* Ensure clean memory before writing */
                *addr &= ~(0xFF << (8 - bit_offset));
                *(addr + 1) &= ~(0xFF >> (bit_offset - 8));

                /* Apply the font row to the screen memory */
                if (bit_offset <= 8) {
                    *addr |= (UINT16)(font_row) << (8 - bit_offset);
                } else {
                    *addr |= (UINT16)(font_row) >> (bit_offset - 8);
                    *(addr + 1) |= (UINT16)(font_row) << (16 - bit_offset);
                }

                addr += 40;  /* Move to the next row */
            }

            x += 8;  /*Ensure proper character spacing */
        }

        text++;
    }
}

/*
 * Draws a bitmap at (x, y) using 32-bit words.
 * 
 * Parameters:
 * - base: Pointer to the screen buffer.
 * - row: Starting row position.
 * - col: Starting column position.
 * - bitmap: Pointer to the 32-bit bitmap data.
 * - height: Number of rows in the bitmap.
 */
void plot_bitmap_32(UINT32 *base, int row, int col, const UINT32 *bitmap, unsigned int height) {
    int i;
    UINT32 *start;
    if (row < 0 || row + height > SCREEN_HEIGHT || col < 0 || col >= SCREEN_WIDTH) 
        return;

    start = base + (row * 20) + (col >> 5); 
    for (i = 0; i < height; i++) {
        *start |= bitmap[i]; 
        start += 20;
    }
    return;
}

/*
 * clear_bitmap_32 - Erases a 32-bit wide bitmap from the screen buffer.
 *
 * This function clears only the bits where the bitmap was drawn using bitwise AND with the
 * inverted bitmap mask. It assumes the bitmap was previously drawn using OR logic.
 *
 * Parameters:
 * - base: Pointer to the start of the screen buffer (UINT32-aligned).
 * - row: Y-coordinate (starting row) where the bitmap was previously drawn.
 * - col: X-coordinate (starting column) where the bitmap was previously drawn.
 * - bitmap: Pointer to the 32-bit bitmap data to erase.
 * - height: Number of rows (height) of the bitmap.
 *
 * Assumptions:
 * - Coordinates are in-bounds.
 * - Bitmap is 32 bits wide (1 longword per row).
 * - The screen buffer uses 20 longwords (80 bytes) per row.
 */
void clear_bitmap_32(UINT32 *base, int row, int col, const UINT32 *bitmap, unsigned int height) {
    int i;
    UINT32 *start;

    if (row < 0 || row + height > SCREEN_HEIGHT || col < 0 || col >= SCREEN_WIDTH) 
        return;

    start = base + (row * 20) + (col >> 5);
    for (i = 0; i < height; i++) {
        *start &= ~(bitmap[i]);
        start += 20;
    }
}

UINT16 *get_video_base() {
    unsigned long base = (((unsigned long)(*VIDEO_BASE_HIGH)) << 16) |
                   (((unsigned long)(*VIDEO_BASE_MID)) << 8);
    return (UINT16 *)base;
}

void set_video_base(UINT16 *base) {
    set_video_base_asm((UINT32)base);
}

