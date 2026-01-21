#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "library_functions.h"

extern Player globalPlayer;

int main() {
    srand(time(NULL));
    clearConsole();

    initPlayer(&globalPlayer);

    while (1) {
        chooseLocation();
        waitForExit();
    }

    cleanup();
    return 0;
}
