#include "core.h"
#include <errno.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include "../notify/notify.h"

int register_epoll(int epoll, int fd) {
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = fd; 
    return epoll_ctl(epoll, EPOLL_CTL_ADD, fd, &ev);
}

void watch(int epoll, EventHandler *events, int events_len) {
    struct epoll_event epoll_events[events_len];
    while (1) {
        int nfds = epoll_wait(epoll, epoll_events, events_len, -1); 
        if (nfds == -1) {
            if (errno == EINTR) continue;
            break;
        }

        for (int i = 0; i < nfds; i++) {
            for (int j = 0; j < events_len; j++) {
                if (events[j].fd == epoll_events[i].data.fd) {
                    char *s = events[j].method();
                    // Notify  
                    notify(s);
                    free(s);
                }
            }
        }
    }
}
