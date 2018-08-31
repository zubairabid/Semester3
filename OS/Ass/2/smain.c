#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Declaring all the functions to be used in the file
int main(int argc, char** argv);
int loop();


/*
 * Setup part of the code, that is executed first and compiles various parts of
 * the shell together.
 */
int main(int argc, char **argv) {
	
	// Load from the configuration file?

	// Run the program loop

	// EXIT, Somehow I guess

}

/* 
 * The REPL part of the shell. Large overview by definition, minor details
 * must be handled by various modules as constructed
 */

int loop() {
	
	char *line;
	char **args;
	int status;

	do {
		line = getline();
		args = parseline();
		status = exec(args);
	} while(1);

}
