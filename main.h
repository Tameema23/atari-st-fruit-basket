/*
 * main_game.h
 * 
 * This header file declares the main game loop functions.
 * 
 * Author: Tameem Aboueldahab, Andres Isturiz
 * Date: 10/03/2025
 */

 #ifndef MAIN_GAME_H
 #define MAIN_GAME_H
 
 #include "model.h"
 
 typedef unsigned long ULONG32;
 
 /* Runs the main game loop */
 void run_game();
 
 void int_to_str(int value, char *buffer);

 /* Gets the current TOS 70Hz clock time */
 ULONG32 get_time();
 
 #endif /* MAIN_GAME_H */
 