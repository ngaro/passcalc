#include <iostream>

using namespace std;

//configuration of passcalc
struct settings {
	bool help = false;
} settings;

//send help to STDOUT, doesn't exit
void showhelp() { cout << "TODO" << endl; }

int main(int argc, char **argv) {
	if(settings.help) { showhelp(); return EXIT_SUCCESS; }
	return EXIT_SUCCESS;
}
