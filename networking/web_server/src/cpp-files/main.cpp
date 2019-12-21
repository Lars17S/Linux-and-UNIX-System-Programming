#include "WebServer.h"

int main(int argc, char* argv[]) {
	WebServer webServer("0.0.0.0", atoi(argv[1]));
	if (webServer.init() != 0)
		return -1;
	webServer.run();
	system("pause");
	return 0;
}