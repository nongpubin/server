#include "wrapper.h"
#include "unistd.h" 


int main()
{
	wrapper server(6666,"192.168.88.49",AF_INET);
    while(1)
	{
		sleep(2000);
	}
}
