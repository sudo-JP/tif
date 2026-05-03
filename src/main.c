#include <stdlib.h>
#include "battery/battery.h"

int main(int argc, char *argv[]) {
    BatteryContext *ctx = battery_init();

    battery_destroy(ctx);
    return EXIT_SUCCESS;
}
