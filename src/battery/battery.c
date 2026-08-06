#include "battery.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Im a good programmer 
BatteryContext *battery_init() {
    BatteryContext *ctx = malloc(sizeof(BatteryContext));
    ctx->percent_fp = fopen(BATTERY_PERCENT_PATH , "r");
    if (ctx->percent_fp == NULL) {
        free(ctx);
        return NULL;
    }
    ctx->charging_fp = fopen(BATTERY_CHARGING_PATH, "r");
    if (ctx->charging_fp == NULL) {
        fclose(ctx->percent_fp);
        free(ctx);
        return NULL;
    }
    
    return ctx;
}

void battery_destroy(BatteryContext *ctx) {
    fclose(ctx->charging_fp);
    fclose(ctx->percent_fp);
    free(ctx);
}

// Something I dont like about C, rust would be better in this 
// case but whatever
// returns true when out is modified with "good" data 
// false otherwise, bad data, unreadable
bool battery_read(BatteryContext *ctx, BatteryState *out) {
    char charging_stat[CHARGING_STAT_BUF_SIZE]; 
    char battery_percent[CHARGING_PERCENT_BUF_SIZE];

    // Rewind each reads 
    rewind(ctx->charging_fp);
    rewind(ctx->percent_fp);

    if (fgets(charging_stat, CHARGING_STAT_BUF_SIZE, ctx->charging_fp) == NULL) {
        return false;
    }
    if (fgets(battery_percent, CHARGING_PERCENT_BUF_SIZE, ctx->percent_fp) == NULL) {
        return false; 
    }

    char *endptr; 
    out->percent = strtol(battery_percent, &endptr, 10);
    if (battery_percent == endptr) return false;
    
    if (strncmp(charging_stat, "Discharging", CHARGING_STAT_BUF_SIZE) == 0) {
        out->charging = false; 
    } else if (strncmp(charging_stat, "Charging", CHARGING_STAT_BUF_SIZE) == 0) {
        out->charging = true; 
    } else {
        return false; 
    }


    return true; 
}


char* battery_format_notification(BatteryState *state) {
    int len = snprintf(NULL, 0, "Battery is at %d", state->percent);
    char *str = malloc(len + 1);
    snprintf(str, len + 1, "Battery is at %d", state->percent);

    return str;
}
