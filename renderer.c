#include "renderer.h"


/* Render the entire game frame */
void render(const GameState *game, UINT16 *base) {
    static GameState prev_game;
    int i;

    if (!game || !base) return;
    render_score(&game->score, base);

    render_basket(&game->basket, (UINT32*)base);
    if (game->basket.x != prev_game.basket.x) {
        render_basket(&game->basket, (UINT32*)base);
    }

    for (i = 0; i < 25; i++) {
        if (game->fruits[i].active && game->fruits[i].y != prev_game.fruits[i].y) {
            render_fruit(&game->fruits[i], base);
        }
    }
    
    for (i = 0; i < 20; i++) {
        if (game->bombs[i].active && game->bombs[i].y != prev_game.bombs[i].y) {
            render_bomb(&game->bombs[i], base);
        }
    }
    

    /* Update score if it changed */
    if (game->score.current_score != prev_game.score.current_score) {
        render_score(&game->score, base);
    }

    /* Save current state for next frame comparison */
    prev_game = *game;
}
void render_basket(const Basket *basket, UINT32 *base) {
    plot_bitmap_32(base, 320, basket->x, basket_bitmap, BASKET_HEIGHT);
}

void render_fruit(const Fruit *fruit, UINT16 *base) {
    if (!fruit) return;
    plot_bitmap_16(base, fruit->y, fruit->x,fruit_bitmap, FRUIT_HEIGHT);
}


void render_bomb(const Bomb *bomb, UINT16 *base) {
    if (!bomb) return;
    plot_bitmap_16(base, bomb->y, bomb->x, bomb_bitmap, BOMB_HEIGHT);
}


void render_score(const Score *score, UINT16 *base) {
    plot_text(base, 560, 5,"Score: " );
    render_score_num(score, base);
}
void render_score_num(const Score *score, UINT16 *base) {
    UINT16 num, hundreds, tens, ones;
    char hund, ten, one;
    char str[2];
    
    if (!score) return;
    num = score->current_score;
    hundreds = num / 100;
    tens = (num / 10) % 10;
    ones = num % 10;

    hund = (char)(hundreds + 48);
    ten = (char)(tens + 48);
    one = (char)(ones + 48);
    
    str[0] = hund;
    str[1] = '\0'; 
    plot_text(base, 616, 5, str);

    str[0] = ten;
    str[1] = '\0';
    plot_text(base, 624, 5, str);

    str[0] = one;
    str[1] = '\0';
    plot_text(base, 632, 5, str);
}


