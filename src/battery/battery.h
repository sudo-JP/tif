#include <stdio.h>
#include <stdbool.h>
#ifndef BATTERY

#define BATTERY_PERCENT_PATH "/sys/class/power_supply/BAT0/capacity"
#define BATTERY_CHARGING_PATH "/sys/class/power_supply/BAT0/status"
#define CHARGING_STAT_BUF_SIZE 16
#define CHARGING_PERCENT_BUF_SIZE 4

typedef struct {
    FILE *percent_fp;
    FILE *charging_fp;
} BatteryContext; 


typedef struct {
    int percent; 
    bool charging;
} BatteryState; 

BatteryContext *battery_init();
void battery_destroy(BatteryContext *ctx);
bool battery_read(BatteryContext *ctx, BatteryState *out);

char* battery_format_notification(BatteryState *state);

#endif 
