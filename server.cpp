#include "server.h"


server::server(int port, std::string ip, int family):port(port),ip(ip),ip_family(family)
{
    std::cout << "server port = " << this->port << std::endl;
    std::cout << "server ip = " << this->ip << std::endl;
    std::cout << "server ip_family = " << this->ip_family << std::endl;
    init();
}

void server::init()
{
    base = event_base_new();
	if (!base) {
		fprintf(stderr, "Could not initialize libevent!\n");
	} else {
        std::cout << "event_base_new ok" << std::endl;
    }

    memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(this->port);
	sin.sin_addr.s_addr = inet_addr(this->ip.c_str());
	listener = evconnlistener_new_bind(base, this->listener_cb, (void *)base,
	                                    LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
	                                     (struct sockaddr*)&sin,sizeof(sin));
	if (!listener) {
		fprintf(stderr, "Could not create a listener!\n");
	} else {
        std::cout << "evconnlistener_new_bind ok" << std::endl;
    }
	signal_event =  evsignal_new(base, SIGINT, this->signal_cb, (void *)base);

	if (!signal_event || event_add(signal_event, NULL)<0) {
		fprintf(stderr, "Could not create/add a signal event!\n");
	}

	log_out("  end ..... ");
	event_base_dispatch(base);
	/*evconnlistener_free(listener);
	event_free(signal_event);
	event_base_free(base);*/
}

server::~server()
{
	log_out("server end .........");
	evconnlistener_free(listener);
	event_free(signal_event);
	event_base_free(base);
}

void server::conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
	if (events & BEV_EVENT_EOF) {
		printf("Connection closed.\n");
	} else if (events & BEV_EVENT_ERROR) {
		printf("Got an error on the connection: %s\n",
		    strerror(errno));/*XXX win32*/
	}
	/* None of the other events can happen here, since we haven't enabled
	 * timeouts */
	bufferevent_free(bev);
}

void server::conn_writecb(struct bufferevent *bev, void *user_data)
{
	/*struct evbuffer *output = bufferevent_get_output(bev);
	if (evbuffer_get_length(output) == 0) {
		printf("flushed answer\n");
		bufferevent_free(bev);
	}*/
}

void  conn_Readcb(struct bufferevent *bev, void *user_data)
{
	char buff[256] = {0};
	struct evbuffer *input = bufferevent_get_input(bev);
	printf("   ...........  %d  \r\n",evbuffer_get_length(input));
 	
	evbuffer_copyout_from(input,0,buff,256);
	printf("   ...........  %s  \r\n",buff);

	/*struct evbuffer *output = bufferevent_get_output(bev);
	printf("flushed answer\n");
	output->*/
	/*if (evbuffer_get_length(output) == 0) {
		printf("flushed answer\n");
		bufferevent_free(bev);
	}*/
}

 void  server::listener_cb(struct evconnlistener *listener, evutil_socket_t fd,struct sockaddr *sa,
            int socklen, void *user_data)
{
	struct event_base *base = (event_base *)user_data;
	struct bufferevent *bev;

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}
	bufferevent_setcb(bev, conn_Readcb, conn_writecb, conn_eventcb, NULL);
	bufferevent_enable(bev, EV_WRITE);
	//bufferevent_disable(bev, EV_READ);
	bufferevent_enable(bev, EV_READ);
	bufferevent_write(bev, "MESSAGE", 25);
}


void server::signal_cb(evutil_socket_t sig, short events, void *user_data)
{
	struct event_base *base = (event_base *)user_data;
	struct timeval delay = { 2, 0 };

	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");
	event_base_loopexit(base, &delay);
}

 void server::SetSignalCallBack(signal_callback cb)
 {
	 set_signal_callback = cb;
 }

 void server::RunCallBack()
 {
	if(set_signal_callback!=NULL){
		set_signal_callback(2,10,NULL);
	}
	log_out("call back ///   ");
 }



