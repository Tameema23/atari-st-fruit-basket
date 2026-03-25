/*
 * input.h
 * 
 * This header file declares functions for handling user input.
 * 
 * Author: Tameem Aboueldahab, Andres Isturiz
 * Date: 10/03/2025
 */

#ifndef INPUT_H
#define INPUT_H

#include "events.h"

#define ESC_KEY     27

int is_key_pressed();
char read_key();
void handle_input(GameState *game);
void set_quit_flag();
int is_quit_pressed();


#endif
