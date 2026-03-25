#include "effects.h"
#include "psg.h"

void play_effect_chime() {
    set_envelope(0x09, 0x0200);
    write_psg(4, 0x30);
    write_psg(5, 0x01);
    enable_channel(2, 1, 0);      /* Channel C: tone only */
    write_psg(10, 0x10);
}

void play_effect_explosion() {
    set_envelope(0x09, 0x0500);
    set_noise(0x07);
    write_psg(4, 0x28);
    write_psg(5, 0x01);
    enable_channel(2, 1, 1);      /* Channel C: tone + noise */
    write_psg(10, 0x10);
}

void play_game_over_melody() {
    enable_channel(2, 1, 0);
    write_psg(4, 0x40); write_psg(5, 0x01);
    write_psg(10, 0x0F); delay_ticks(8);

    write_psg(4, 0x60); delay_ticks(8);
    write_psg(4, 0x80); delay_ticks(8);
    write_psg(4, 0x90); delay_ticks(10);

    write_psg(10, 0x00);
}

void play_effect_victory() {
    enable_channel(2, 1, 0);
    write_psg(4, 0x80); write_psg(5, 0x01);
    write_psg(10, 0x0F); delay_ticks(8);

    write_psg(4, 0x65); delay_ticks(8);
    write_psg(4, 0x50); delay_ticks(12);

    write_psg(10, 0x00);
}

void play_effect_spawn() {
    set_envelope(0x09, 0x0100);
    write_psg(4, 0x50);
    write_psg(5, 0x01);
    enable_channel(2, 1, 0);      /* Channel C: tone only */
    write_psg(10, 0x10);
}
