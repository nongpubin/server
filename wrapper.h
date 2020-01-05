#ifndef     _WRAPPER_H_
#define    _WRAPPER_H_


#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#ifndef _WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/util.h"
#include "event2/event.h"
#include <iostream>
#include "log.h"


class wrapper
{
public:
    wrapper(int port, std::string ip, int family);
    void server_init();
    ~wrapper();

    static void signal_cb(evutil_socket_t sig, short events, void *user_data);
    static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd,struct sockaddr *sa,int socklen, void *user_data);
    static void conn_writecb(struct bufferevent *bev, void *user_data);
    static void conn_eventcb(struct bufferevent *bev, short events, void *user_data);

    void (*register_signal_callback)(evutil_socket_t sig, short events, void *user_data);
    void (*register_listener_callback)(struct evconnlistener *listener, evutil_socket_t fd,struct sockaddr *sa,int socklen, void *user_data);
    void (*register_write_callback)(struct bufferevent *bev, void *user_data);
    void (*register_event_callback)(struct bufferevent *bev, short events, void *user_data);
    
    
private:
    int port;
    std::string ip;
    int ip_family;

    struct event_base *base;
	struct evconnlistener *listener;
	struct event *signal_event;
	struct sockaddr_in sin;

};


#endif



