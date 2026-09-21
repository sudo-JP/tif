#ifndef CORE

typedef struct EventHandler_struct {
    int fd; 
    char* (*method)(void);
} EventHandler;

int register_epoll(int epoll, int fd);
void watch(int epoll, EventHandler *events, int events_len);

#endif 
