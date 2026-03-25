/*
 * input.c
 * 
 * This file handles asynchronous keyboard input for the Fruit Basket game.
 * 
 * Author: Tameem Aboueldahab, Andres Isturiz
 * Date: 10/03/2025
 */

#include "input.h"
#include <osbind.h>

/*
 * Checks if a key is pressed.
 * 
 * Returns:
 * - 1 if a key is available, 0 otherwise.
 */
int is_key_pressed() {
    return  Cconis();
}

/*
 * Reads the pressed key (non-blocking).
 * 
 * Returns:
 * - The ASCII value of the key if pressed, otherwise 0.
 */
char read_key() {
    if (is_key_pressed()) {
        return (char)Cnecin();
    }
    return 0;
}

/*
 * Handles user input and updates the game state accordingly.
 * 
 * Parameters:
 * - game: Pointer to the current game state.
 */
void handle_input(GameState *game) {
    char key = read_key();
    if (key == 'a') {
        handle_move_left(game);
    } else if (key == 'd') {
        handle_move_right(game);
    } else if (key == ESC_KEY) {
        set_quit_flag();
    }
}

static int quit_flag = 0;

void set_quit_flag() {
    quit_flag = 1;
}

int is_quit_pressed() {
    return quit_flag;
}
