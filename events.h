/*  
 * events.h
 * 
 * This header file declares functions for handling user inputs and updating the game state.
 * 
 * Author: Andres Isturiz, Tameem Aboueldahab  
 * Date: 28/02/25  
 */

 #ifndef EVENTS_H
 #define EVENTS_H
 
 #include "model.h"
 #include "input.h"
 
 /* Function Prototypes */
 void handle_move_left(GameState *game);
 void handle_move_right(GameState *game);
 void handle_update(GameState *game);
 
 
 #endif /* EVENTS_H */
 