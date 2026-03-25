/*  
 * events.c
 * 
 * This file handles user inputs and updates the game state.
 * It includes functions for moving the basket and updating the game logic.
 * 
 * Author: Tameem Aboueldahab, Andres Isturiz  
 * Date: 28/02/25  
 */

 #include "events.h"
 #include "effects.h"
 #include <stdio.h>
 
 /*
  * Moves the basket left.
  *
  * Parameters:
  * - game: Pointer to the game state.
  */
 void handle_move_left(GameState *game) {
     move_basket(&game->basket, -1);
 }
 
 /*
  * Moves the basket right.
  *
  * Parameters:
  * - game: Pointer to the game state.
  */
 void handle_move_right(GameState *game) {
     move_basket(&game->basket, 1);
 }
 
 /*
  * Updates the game state by moving objects and handling collisions.
  *
  * Parameters:
  * - game: Pointer to the game state.
  */
 void handle_update(GameState *game) {
    int i;
    int score = game->score.current_score;
    /* Update active fruits and handle collisions */
    for (i = 0; i < 40; i++) {
        if (game->fruits[i].active) {
            if (check_collision(&game->basket, &game->fruits[i])) {
                play_effect_chime();
                game->score.current_score += game->fruits[i].value;
                game->fruits[i].active = 0;
                continue;
            }
        }
    }

    /* Update active bombs and handle collisions */
    for (i = 0; i < 50; i++) {
        if (game->bombs[i].active) {
            if (check_bomb_collision(&game->basket, &game->bombs[i])) {
                play_effect_explosion();
                play_game_over_melody();
                game->bombs[i].active = 0;
                game->game_over = 1;
                set_quit_flag();
                return;
            }
        }
    }

    /* Move basket */
    handle_input(game);

    update_fruits(game->fruits, game->start_time);
    update_bombs(game->bombs, game->fruits, game->start_time);
    
}



 