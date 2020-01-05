#include "wrapper.h"
#include "unistd.h" 

#include "json.h"


int main()
{
	log_out("hello");
	log_out(255);

	Json::Value test;
	test["name"] = "nongpubin";
	log_out(test["name"].asString());
	wrapper server(6666,"192.168.88.49",AF_INET);
}
