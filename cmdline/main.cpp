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

//sends standard errormessage plus 'extrainfo' to STDERR, exits with 'errorcode'
void showerror(int errorcode, const char* extrainfo) {
	cerr << "ERROR " << errorcode << ": ";
	switch(errorcode) {
	case 1: cerr << "Unknown option '" << extrainfo << "'"; break;
	default: cerr <<"Unknown error";
	}
	cerr << endl;
	exit(errorcode);
}

//send help to STDOUT, doesn't exit
void showhelp() { cout << "TODO" << endl; }

//set settings and show errors for unknown args
void args_to_settings(int argc, char **argv) {
	int current_cmdarg;	//Although we use this for regular chars, getopt_long returns int's (also needed for the -1 check)
	opterr = 0;	//Don't use the system's default errors
	while ((current_cmdarg = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
		switch(current_cmdarg) {
		case 'h': settings.help = true; break;
		default: optind--; showerror(1, argv[optind]);
		}
	}
}

int main(int argc, char **argv) {
	args_to_settings(argc, argv);
	if(settings.help) { showhelp(); return EXIT_SUCCESS; }
	return EXIT_SUCCESS;
}
