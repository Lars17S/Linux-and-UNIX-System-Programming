#include "MultiClientChat.h"

int main(int argc, char* argv[]) {
	MultiClientChat mcc("0.0.0.0", atoi(argv[1]));
	if (mcc.init() != 0)
		return -1;
	mcc.run();
	system("pause");
	return 0;
}