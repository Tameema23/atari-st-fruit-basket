 /*
 * Music playback module for Fruit Basket
 * Authors: Tameem Aboueldahab & Andres Isturiz
 * Description: Plays a looping upbeat melody using PSG channel A.
 */

#include "music.h"
#include "psg.h"

typedef struct {
    int tone;
    int duration;
} Note;

#define MELODY_LEN 48

static Note melody[MELODY_LEN] = {
    {239, 4},  /* E3 */
    {284, 4},  /* D3 */
    {318, 4},  /* C3 */
    {239, 4},  /* E3 */
    {213, 6},  /* G3 */
    {179, 6},  /* B3 */
    {239, 8},  /* E3 */
    {318, 4},  /* C3 */

    {239, 4},  /* E3 */
    {213, 4},  /* G3 */
    {190, 4},  /* A3 */
    {213, 4},  /* G3 */
    {239, 6},  /* E3 */
    {284, 4},  /* D3 */
    {213, 8},  /* G3 */
    {239, 6},  /* E3 */

    {239, 4},  /* E3 */
    {284, 4},  /* D3 */
    {318, 4},  /* C3 */
    {239, 4},  /* E3 */
    {213, 6},  /* G3 */
    {179, 6},  /* B3 */
    {190, 8},  /* A3 */
    {213, 6},  /* G3 */

    {239, 4},  /* E3 */
    {213, 4},  /* G3 */
    {190, 4},  /* A3 */
    {213, 4},  /* G3 */
    {239, 6},  /* E3 */
    {284, 4},  /* D3 */
    {239, 8},  /* E3 */
    {318, 6},  /* C3 */

    {239, 4},  /* E3 */
    {253, 4},  /* F3 */
    {284, 4},  /* D3 */
    {213, 4},  /* G3 */
    {190, 6},  /* A3 */
    {239, 6},  /* E3 */
    {318, 8},  /* C3 */
    {253, 6},  /* F3 */

    {239, 4},  /* E3 */
    {213, 4},  /* G3 */
    {190, 4},  /* A3 */
    {239, 4},  /* E3 */
    {213, 6},  /* G3 */
    {179, 6},  /* B3 */
    {239, 8},  /* E3 */
    {318, 6}   /* C3 */
};




static int current_note = 0;
static int ticks_remaining = 0;

void start_music() {
    current_note = 0;
    ticks_remaining = melody[0].duration;
    set_tone(0, melody[0].tone);
    set_volume(0, 10);
    enable_channel(0, 1, 0);
}

void update_music(ULONG32 time_elapsed) {
    if (--ticks_remaining <= 0) {
        current_note = (current_note + 1) % MELODY_LEN;
        set_tone(0, melody[current_note].tone);
        ticks_remaining = melody[current_note].duration;
    }
}
