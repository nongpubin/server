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
#include <functional>

typedef std::function<void(evutil_socket_t sig, short events, void *user_data)> signal_callback;

class server
{
public:
    server(int port, std::string ip, int family);
    void init();
    ~server();

    static void signal_cb(evutil_socket_t sig, short events, void *user_data);
    static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd,struct sockaddr *sa,int socklen, void *user_data);
    static void conn_writecb(struct bufferevent *bev, void *user_data);
    static void conn_eventcb(struct bufferevent *bev, short events, void *user_data);
    
    void SetSignalCallBack(signal_callback cb);
    void RunCallBack();
private:
    int port;
    std::string ip;
    int ip_family;

    struct event_base *base;
	struct evconnlistener *listener;
	struct event *signal_event;
	struct sockaddr_in sin;

    signal_callback set_signal_callback;
};
 
#endif



