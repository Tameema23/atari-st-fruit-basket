/*
 * PSG (Programmable Sound Generator) low-level control
 * Authors: Tameem Aboueldahab & Andres Isturiz
 */

 #include "psg.h"
 #include <osbind.h>
 
 #define PSG_SELECT 0xFF8800
 #define PSG_WRITE  0xFF8802
 #define PSG_READ   0xFF8800
 
 void write_psg(int reg, UINT8 val) {
    long old_ssp = Super(0);
     if (reg < 0 || reg > 15) return;
     *((volatile UINT8 *)PSG_SELECT) = reg;
     *((volatile UINT8 *)PSG_WRITE) = val;
     Super(old_ssp);
 }
 
 UINT8 read_psg(int reg) {
    long old_ssp = Super(0);
    UINT8 val = 0;

    if (reg >= 0 && reg <= 15) {
        *((volatile UINT8 *)PSG_SELECT) = reg;
        val = *((volatile UINT8 *)PSG_READ);
    }

    Super(old_ssp);
    return val;
}

 void set_tone(int channel, int tuning) {
    int coarse, fine;
     if (channel < 0 || channel > 2) return;
     coarse = (tuning >> 8) & 0x0F;
     fine = tuning & 0xFF;
     write_psg(channel * 2, fine);
     write_psg(channel * 2 + 1, coarse);
 }
 
 void set_volume(int channel, int volume) {
     if (channel < 0 || channel > 2 || volume < 0 || volume > 15) return;
     write_psg(8 + channel, volume);
 }
 
 void enable_channel(int channel, int tone_on, int noise_on) {
    UINT8 mixer = read_psg(7);

    if (channel == 2) {
        if (tone_on)
            mixer &= ~(1 << 2);
        else
            mixer |= (1 << 2);

        if (noise_on)
            mixer &= ~(1 << 5);
        else
            mixer |= (1 << 5);
    }

    write_psg(7, mixer);
}


void stop_sound() {
    int r, ch;
    /* Mute all channels */
    for (ch = 0; ch < 3; ch++) {
        write_psg(8 + ch, 0x00);  /* Volume = 0 */
    }

    /* Disable all tones and noises (R7 = 0x3F = 0011 1111) */
    write_psg(7, 0x3F);

    /* Stop envelope playback */
    write_psg(13, 0x00);

    for (r = 0; r <= 5; r++) {
        write_psg(r, 0x00);
    }
    
    write_psg(6, 0x00);
}
 
 void set_noise(int tuning) {
     if (tuning < 0 || tuning > 31) return;
     write_psg(6, tuning);
 }
 
 void set_envelope(int shape, unsigned int sustain) {
     write_psg(11, sustain & 0xFF);
     write_psg(12, (sustain >> 8) & 0xFF);
     write_psg(13, shape & 0x0F);
 }
 
 void delay_ticks(int ticks) {
     ULONG32 start = get_time();
     while ((get_time() - start) < (ULONG32)ticks);
 }
 