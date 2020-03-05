#include <getopt.h>
#include <iostream>

using namespace std;

//possible commandline args
static const char* const short_options = "h";
static const struct option long_options[] = {
	{ "help", no_argument, NULL, 'h' },
	{ NULL, 0, NULL, 0 }
};

//configuration of passcalc
struct settings {
	bool help = false;
} settings;

//send help to STDOUT, doesn't exit
void showhelp() { cout << "TODO" << endl; }

//set settings and show errors for unknown args
void args_to_settings(int argc, char **argv) {
	int current_cmdarg;	//Although we use this for regular chars, getopt_long returns int's (also needed for the -1 check)
	while ((current_cmdarg = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
		switch(current_cmdarg) {
		case 'h': settings.help = true; break;
		}
	}
}

int main(int argc, char **argv) {
	args_to_settings(argc, argv);
	if(settings.help) { showhelp(); return EXIT_SUCCESS; }
	return EXIT_SUCCESS;
}
