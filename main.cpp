#include "wrapper.h"
#include "unistd.h" 


int main()
{
	log_out("hello");
	log_out(255);
	wrapper server(6666,"192.168.88.49",AF_INET);
}
