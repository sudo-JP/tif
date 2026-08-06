#include <stdlib.h>
#include "battery/battery.h"
#include "notify/notify.h"

int main(int argc, char *argv[]) {
    BatteryContext *ctx = battery_init();
    BatteryState state;
    if (battery_read(ctx, &state)) {

    }

    char* battery_str = battery_format_notification(&state);
    notify("Low Battery", battery_str);
    free(battery_str);

    battery_destroy(ctx);
    return EXIT_SUCCESS;
}
