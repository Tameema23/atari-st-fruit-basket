#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
#include "raster.h"

#define BASKET_HEIGHT 32
#define FRUIT_HEIGHT 16
#define BOMB_HEIGHT 16


void render(const GameState *game, UINT16 *base);
void render_basket(const Basket *basket, UINT32 *base);
void render_fruit(const Fruit *fruit, UINT16 *base);
void render_bomb(const Bomb *bomb, UINT16 *base);
void render_score(const Score *score, UINT16 *base);
void render_score_num(const Score *score, UINT16 *base);


extern const UINT32 basket_bitmap[BASKET_HEIGHT] = {
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,  
    0x40000002,  
    0x60000006,  
    0x7000000E,  
    0x0FFFFFFC
};



extern const UINT16 bomb_bitmap[BOMB_HEIGHT] = {
    0x0000,
    0x007E,
    0x004E,
    0x00C6,
    0x0F88,
    0x1818,
    0x2004,
    0x2004,
    0x2004,
    0x1008,
    0x0FC0,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000
};

extern const UINT16 fruit_bitmap[FRUIT_HEIGHT] = {
    0x0000,  
    0x0060,  
    0x0040,  
    0x00C0,  
    0x0F80,  
    0x1818,  
    0x2004,  
    0x2004,  
    0x2004,  
    0x1008,  
    0x0FC0,   
    0x0000,  
    0x0000,  
    0x0000,  
    0x0000,  
    0x0000   
};

#endif
