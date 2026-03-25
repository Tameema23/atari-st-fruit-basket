#include <osbind.h>
#include "psg.h"
#include "effects.h"
#include "music.h"

extern ULONG32 get_time();


int main() {
    ULONG32 now, then;
    char ch;
    int i;
    int music_playing = 0;

    Cconws("Press:\r\n");
    Cconws("  'f' = fruit chime\r\n");
    Cconws("  'b' = bomb explosion\r\n");
    Cconws("  'v' = victory melody\r\n");
    Cconws("  'g' = game over melody\r\n");
    Cconws("  'p' = spawn sound\r\n");
    Cconws("  'm' = start music\r\n");
    Cconws("  's' = stop music\r\n");
    Cconws("  'q' = quit\r\n");
    
    then = get_time();

    while (1) {
        now = get_time();

        /* Update music if it's playing */
        if (music_playing && now != then) {
            update_music(now - then);
            then = now;
        }

        /* Handle key input */
        if (Cconis()) {
            ch = (char)Cnecin();

            switch (ch) {
                case 'f':
                    play_effect_chime();
                    delay_ticks(40);  /* ~0.7 sec to hear fade */
                    break;

                case 'b':
                    play_effect_explosion();
                    delay_ticks(60);
                    
                    break;

                case 'v':
                    play_effect_victory();
                    delay_ticks(50);
                    break;

                case 'g':
                    play_game_over_melody();
                    delay_ticks(50);
                    break;

                case 'p':
                    play_effect_spawn();
                    break;

                case 'm':
                    start_music();
                    music_playing = 1;
                    break;

                case 's':
                    stop_sound();
                    music_playing = 0;
                    break;

                case 'q':
                    stop_sound();
                    return 0;
            }
        }

        delay_ticks(1);
    }

    return 0;
}
