#include <stdio.h>
#include <sys/utsname.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

#include "disp.h"

int prompt() {
	struct utsname buf;
	char *user = (char*)malloc(HOST_NAME_MAX * sizeof(char*));
	char *cdir = (char*)malloc(PATH_MAX * sizeof(char*));

	// Getting system details
	uname(&buf);
	// hostname, path (might want error checking on this lad)
	user = getenv("USER");
	getcwd(cdir, PATH_MAX);

	printf("\n<%s@%s:%s> ", user, buf.nodename, cdir);

	return 1;
}
