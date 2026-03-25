/*  
 * RASTER.H
 * 
 * This header file defines the raster graphics functions for the Atari ST.
 * It includes function prototypes and macro definitions for drawing operations.
 * 
 * Author: Andres Isturiz Tameem Aboueldahab
 * Date: 28/02/25  
 */ 
#ifndef RASTER_H
#define RASTER_H

typedef unsigned long UINT32;
typedef unsigned int UINT16;
typedef unsigned char UINT8;

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 400
#define WORD_SIZE 16
#define SCREEN_WORD_WIDTH 40
#define INVADER_HEIGHT 16
#define INVADER_WIDTH 16
#define SCREEN_SZ_LONG 8000

UINT16 *get_video_base();
void set_video_base(UINT16 *base);

void clear_screen(UINT32 *base);
void plot_pixel(UINT8 *base, int x, int y);
void plot_hline(UINT8 *base, int x1, int x2, int y);
void plot_vline(UINT8 *base, int x, int y1, int y2);
void plot_bitmap_16(UINT16 *base, int row, int col, const UINT16 *bitmap, unsigned int height);
void plot_text(UINT16 *base, int x, int y, const char *text);
void plot_gline(UINT8 *base, int x1, int y1, int x2, int y2);
void plot_bitmap_32(UINT32 *base, int row, int col, const UINT32 *bitmap, unsigned int height);
void clear_bitmap_32(UINT32 *base, int row, int col, const UINT32 *bitmap, unsigned int height);

extern const UINT16 background_bitmap[16] = {
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000
};


#endif
