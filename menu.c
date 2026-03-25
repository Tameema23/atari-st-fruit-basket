#include "menu.h"
#include "raster.h"
#include <osbind.h>
#include "psg.h"

#define MENU_OPTION_COUNT 2
const char *menu_options[MENU_OPTION_COUNT] = {"1 PLAYER", "QUIT"};

int splash_screen(unsigned int *screen) {
    int i;
    clear_screen((UINT32 *)screen);

    for (i = 1; i <= 4; i++) {
        if (i >= 1) plot_text(screen, 112, 100, "FRUIT BASKET");
        if (i >= 2) plot_text(screen, 96, 140, "CATCH THE FRUIT!");
        if (i >= 3) plot_text(screen, 96, 160, "AVOID THE BOMBS!");
        if (i >= 4) plot_text(screen, 80, 200, "PRESS ANY KEY TO START...");

        Setscreen(screen, screen, -1);
        delay_ticks(30);
    }

    while (!Cconis());
    (void)Cnecin();
    clear_screen((UINT32 *)screen);  /* Clear before game begins */

    return 1;
}
