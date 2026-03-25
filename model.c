/*  
 * model.c
 * 
 * This file defines the game logic and manages object behaviors such as movement and collisions.
 * 
 * Author: Andres Isturiz  
 * Date: 28/02/25  
 */
#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "effects.h"


/*
 * Moves the basket left or right.
 * 
 * Parameters:
 * - basket: Pointer to the basket structure.
 * - direction: Direction to move (-1 for left, 1 for right).
 */
void move_basket(Basket *basket, int direction) {
    basket->x += direction * basket->velocity;
    if (basket->x < 0) basket->x = 0;
    if (basket->x > SCREEN_WIDTH - BASKET_WIDTH) basket->x = SCREEN_WIDTH - BASKET_WIDTH;
}


 /* Enhanced random position generator */
 int get_random_position(int range) {
     return rand() % range;
 }
 
 /* Returns a small random offset to position bombs near the fruit */
 int get_random_offset() {
     return (rand() % 21) - 10; 
 }
 
 /* Initializes the game state */
 void initialize_game(GameState *game) {
     int i;
     game->game_over = 0;
     game->start_time = get_time();
     game->basket.x = SCREEN_WIDTH / 2;
     game->basket.velocity = 25;
     game->score.current_score = 0;
 
     for (i = 0; i < 40; i++) {
         game->fruits[i].x = get_random_position(SCREEN_WIDTH - FRUIT_WIDTH);
         game->fruits[i].y = 0;
         game->fruits[i].velocity = 1 + (rand() % 2);game->fruits[i].value = 5;
         
         game->fruits[i].active = (i < 3) ? 1 : 0;
     }
 
     for (i = 0; i < 50; i++) {
         game->bombs[i].x = get_random_position(SCREEN_WIDTH - BOMB_WIDTH);
         game->bombs[i].y = 0;
         game->bombs[i].velocity = 2 + (rand() % 2);
         game->bombs[i].active = (i < 4) ? 1 : 0;
     }
 }
 
 /* Updates fruit positions and spawns new ones */
 void update_fruits(Fruit *fruits, unsigned long start_time) {
     int i, spawn_rate;
     static int spawn_timer = 0;
     int active_count = 0;
     int seconds = get_elapsed_seconds(start_time);
 
     for (i = 0; i < 40; i++) {
         if (fruits[i].active) {
             fruits[i].y += fruits[i].velocity;
             if (fruits[i].y > SCREEN_HEIGHT) {
                 fruits[i].active = 0;
             }
             active_count++;
         }
     }
 
     if (active_count < 15) {
         spawn_timer++;
         spawn_rate = 90 - (seconds / 2);
         if (spawn_rate < 30) spawn_rate = 30;
 
         if (spawn_timer >= spawn_rate) {
             for (i = 0; i < 40; i++) {
                 if (!fruits[i].active) {
                     fruits[i].active = 1;
                     fruits[i].x = get_random_position(SCREEN_WIDTH - FRUIT_WIDTH);
                     fruits[i].y = 0;
                     fruits[i].velocity = 3 + (seconds / 20);
                     break;
                 }
             }
             spawn_timer = 0;
         }
     }
 }
 
 /* Updates bomb positions and spawns new ones near fruits */
 void update_bombs(Bomb *bombs, Fruit *fruits, unsigned long start_time) {
     int i, spawn_rate, fruit_index, offset;
     static int spawn_timer = 0;
     int active_count = 0;
     int seconds = get_elapsed_seconds(start_time);
 
     for (i = 0; i < 50; i++) {
         if (bombs[i].active) {
             bombs[i].y += bombs[i].velocity;
             if (bombs[i].y > SCREEN_HEIGHT) {
                 bombs[i].active = 0;
             }
             active_count++;
         }
     }
 
     if (active_count < 15) {
         spawn_timer++;
         spawn_rate = 60 - (seconds / 2);
         if (spawn_rate < 20) spawn_rate = 20;
 
         if (spawn_timer >= spawn_rate) {
             for (i = 0; i < 50; i++) {
                 if (!bombs[i].active) {
                     bombs[i].active = 1;
                     fruit_index = rand() % 25;
                     offset = get_random_offset();
                     bombs[i].x = fruits[fruit_index].x + offset;
                     if (bombs[i].x < 0) bombs[i].x = 0;
                     if (bombs[i].x > SCREEN_WIDTH - BOMB_WIDTH) bombs[i].x = SCREEN_WIDTH - BOMB_WIDTH;
                     bombs[i].y = 0;
                     bombs[i].velocity = 4 + (seconds / 15);
                     break;
                 }
             }
             spawn_timer = 0;
         }
     }
 }
 

/*
 * Checks if a fruit collides with the basket.
 * A collision occurs if the fruit reaches the basket's height and its x-coordinate is within the basket's range.
 * 
 * Parameters:
 * - basket: Pointer to the basket structure.
 * - fruit: Pointer to the fruit structure.
 * 
 * Returns:
 * - 1 if a collision is detected, 0 otherwise.
 */
int check_collision(Basket *basket, Fruit *fruit) {
    return !(fruit->x + FRUIT_WIDTH < basket->x ||
             fruit->x > basket->x + BASKET_WIDTH ||
             fruit->y + FRUIT_HEIGHT < BASKET_Y ||
             fruit->y > BASKET_Y + BASKET_HEIGHT);
}

/*
 * Checks if a bomb collides with the basket.
 * A collision occurs if the bomb reaches the basket's height and its x-coordinate is within the basket's range.
 * 
 * Parameters:
 * - basket: Pointer to the basket structure.
 * - bomb: Pointer to the bomb structure.
 * 
 * Returns:
 * - 1 if a collision is detected, 0 otherwise.
 */
int check_bomb_collision(Basket *basket, Bomb *bomb) {
    int basket_left = basket->x;
    int basket_right = basket->x + BASKET_WIDTH;
    int basket_top = BASKET_Y;
    int basket_bottom = BASKET_Y + BASKET_HEIGHT;

    int bomb_left = bomb->x;
    int bomb_right = bomb->x + BOMB_WIDTH;
    int bomb_top = bomb->y;
    int bomb_bottom = bomb->y + BOMB_HEIGHT;

    if (bomb_right >= basket_left && 
        bomb_left <= basket_right && 
        bomb_bottom >= basket_top && 
        bomb_top <= basket_bottom) {
        return 1; 
    }

    return 0; 
}

int get_elapsed_seconds(unsigned long start_time) {
    return (get_time() - start_time) / 70;
}


