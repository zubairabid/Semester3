#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "util.h"
#include "disp.h"
#include "operation.h"

// Declaring all the functions to be used in the file
int main();
int loop();


/*
 * Setup part of the code, that is executed first and compiles various parts of
 * the shell together.
 */
int main() {

	// Load from the configuration file?

	// Run the program loop
	loop();

	// EXIT, Somehow I guess

}

/*
 * The REPL part of the shell. Large overview by definition, minor details
 * must be handled by various modules as constructed
 */

int loop() {

	size_t bsize = 0;
	char *line = (char*)malloc(bsize);
	char **lines;
	char **argv;
	int argc;
	int status, i, num;

	do {
		prompt();
		getline(&line, &bsize, stdin);

		// deal with blank input
		if (*line == (char)10)
			continue;

		lines = splitlines(line, &num);

		for(i = 0; i < num; i++) {
			line = lines[i];

			// blank input
			if (*line == (char)10) {
				// perror("Please input something");
				continue;
			}

			argv = parseline(line, &argc);
			status = run(argv, argc);
			if(status == 0)
				break;
		}

	} while(status != 0);

	return 0;
}
