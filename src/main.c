#include <stdlib.h>
#include "battery/battery.h"
#include "core/core.h"
#include "notify/notify.h"
#include <sys/epoll.h>

static BatteryContext *ctx;

char* battery_callback(void) {
    BatteryState state;
    battery_read(ctx, &state);
    return battery_format_notification(&state);
}

int main(int argc, char *argv[]) {
    ctx = battery_init();
    if (ctx == NULL) return EXIT_FAILURE;
    EventHandler handler;
    handler.fd = ctx->timer_fd;
    handler.method = battery_callback;

    int epoll = epoll_create1(0);
    if (epoll == -1) return EXIT_FAILURE;
    register_epoll(epoll, ctx->timer_fd, &handler);
    watch(epoll, &handler, 1);

    battery_destroy(ctx);
    return EXIT_SUCCESS;
}
