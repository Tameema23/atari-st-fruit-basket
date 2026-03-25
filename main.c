/*
 * main_game.c
 *
 * This file contains the main game loop for the Fruit Basket game.
 * It manages animation, input handling, and rendering in a structured manner.
 *
 * Author: Tameem Aboueldahab, Andres Isturiz
 * Date: 10/03/2025
 */

 #include "main.h"
 #include "renderer.h"
 #include "input.h"
 #include "events.h"
 #include "music.h"
 #include "psg.h"
 #include "raster.h"
 #include "menu.h"
 #include <osbind.h>
 
 int main() {
     run_game();
     return 0;
 }
 
 /* Function to get the current time from the TOS 70Hz clock */
 ULONG32 get_time() {
     ULONG32 time;
     long old_ssp = Super(0);  /* Enter privileged mode */
     time = *((ULONG32 *)0x462);
     Super(old_ssp);  /* Exit privileged mode */
     return time;
 }
 
 
 /*
  * Main game loop
  * Handles input polling, game state updates, and rendering.
  */
 void run_game() {
    int i;
    GameState game;
    UINT16 *frontBuffer;
    UINT16 *backBuffer;
    UINT16 *temp;
    UINT16 *originalBackBuffer;
    ULONG32 timeNow, timePrev;
    ULONG32 swapTime;
    long old_ssp;
    char score_text[20];
    ULONG32 music_time_prev = get_time();


    frontBuffer = (UINT16 *)Physbase();

    /* Show splash screen */
    if (splash_screen(frontBuffer) != 1) {
        return;
    }


    /* Allocate memory for the back buffer (ensure 256-byte alignment) */
    originalBackBuffer = (UINT16 *)Malloc(32000 + 256);
    if (!originalBackBuffer) {
        Cconws("Error: Could not allocate back buffer.\r\n");
        return;
    }
    backBuffer = (UINT16 *)(((ULONG32)originalBackBuffer + 255) & ~255);

    initialize_game(&game);
    clear_screen((UINT32*)backBuffer);
    render(&game, backBuffer);
    start_music();
    old_ssp = Super(0);
    *((char *)0x484) = 0;
    Super(old_ssp);


    timePrev = get_time();

    while (!is_quit_pressed()) {
        timeNow = get_time();

        if (timeNow != timePrev) {
            old_ssp = Super(0);
            Setscreen(backBuffer, frontBuffer, -1);
            Super(old_ssp);

            swapTime = get_time();
            while (get_time() == swapTime);

            /* Clear only the back buffer */
            clear_screen((UINT32*)backBuffer);
            
            handle_input(&game);
            
            /* Update game state and redraw */
            handle_update(&game);
            render(&game, backBuffer);

            if (timeNow != music_time_prev) {
                update_music(1);
                music_time_prev = timeNow;
            }

            /* Swap buffer pointers */
            temp = frontBuffer;
            frontBuffer = backBuffer;
            backBuffer = temp;

            timePrev = timeNow;
        }
    }

    stop_sound();

    /* Clear screen before game over text */
    clear_screen((UINT32*)frontBuffer);
    old_ssp = Super(0);
    Setscreen(frontBuffer, frontBuffer, -1);
    Super(old_ssp);

    /* Fade-in text animation */
    int_to_str(game.score.current_score, score_text);
    for (i = 0; i <= 3; i++) {
        if (i >= 1) plot_text(frontBuffer, 96, 150, "GAME OVER!");
        if (i >= 2) plot_text(frontBuffer, 96, 170, "FINAL SCORE:");
        if (i >= 3) plot_text(frontBuffer, 224, 170, score_text);

        old_ssp = Super(0);
        Setscreen(frontBuffer, frontBuffer, -1);
        Super(old_ssp);
        delay_ticks(40);
    }

    plot_text(frontBuffer, 80, 190, "PRESS ANY KEY TO EXIT...");

    while (!Cconis());
    (void)Cnecin();

    /* Final cleanup and screen restore */
    old_ssp = Super(0);
    *((char *)0x484) = 1; /* Re-enable sound */
    Super(old_ssp);

    clear_screen((UINT32*)frontBuffer);
    Setscreen(frontBuffer, frontBuffer, -1);
    Mfree(originalBackBuffer);
}

void int_to_str(int value, char *buffer) {
    int i = 0, j, temp;
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    while (value > 0 && i < 10) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }
    buffer[i] = '\0';

    for (j = 0; j < i / 2; j++) {
        temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}
