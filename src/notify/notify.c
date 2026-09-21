#include "notify.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void notify(const char *summary) {
    char buffer[strlen(summary) + 12 + 1];
    snprintf(buffer, sizeof(buffer), "notify-send %s", summary);
    system(buffer);
}
