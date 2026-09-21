#include "core.h"
#include <errno.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include "../notify/notify.h"
#include <unistd.h>

int register_epoll(int epoll, int fd, void *ptr) {
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.ptr = ptr; 
    return epoll_ctl(epoll, EPOLL_CTL_ADD, fd, &ev);
}

// This function shouldn't return 
void watch(int epoll, EventHandler *events, int events_len) {
    struct epoll_event epoll_events[events_len];
    while (1) {
        int nfds = epoll_wait(epoll, epoll_events, events_len, -1); 
        if (nfds == -1) {
            if (errno == EINTR) continue;
            break;
        }

        for (int i = 0; i < nfds; i++) {
            EventHandler *h = (EventHandler *)epoll_events[i].data.ptr;
            uint64_t expirations;
            if (read(h->fd, &expirations, sizeof(expirations)) == -1) {
                return;
            }

            char *s = h->method();
            if (s == NULL) {
                continue;
            }
            notify(s);
            free(s);
        }
    }
}
