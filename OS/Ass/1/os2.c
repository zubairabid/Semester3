#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>

#define MAX_BUFF 4096

void permission_lena_chahiye_na(char*, char*);

int len(char str[]) {
	int i = 0;
	while(str[i] != '\0') {
		i++;
	}
	return i;
}

int wstdout(char str[]) {
	write(1, str, len(str));
	write(1, "\n", 1);
}

int main(){

	char buffer[MAX_BUFF];
	char rbuf[MAX_BUFF];

	// Checking for existence of Directory
	struct stat stats;
	int exists;
	exists = lstat("Assignment", &stats);

	if(exists == 0 && S_ISDIR(stats.st_mode) == 1) {
		wstdout("Checking whether the directory has been created: Yes");
	}
	else{
		wstdout("Checking whether the directory has been created: No");
	}


	// Checking for existence of input file
	exists = lstat("Assignment/outfile", &stats);
	// printf("%d %lo", stats.st_mode, stats.st_mode);

	//if(exists == 0 && stats.st_mode == 33216) {
	if((stats.st_mode & S_IFMT) == S_IFREG) {
		wstdout("Checking whether the file has been created: Yes");
	}
	else{
		wstdout("Checking whether the file has been created: No");
	}



	// Making a symlink
	int success = symlink("Assignment/outfile", "outfile");



	// Checking for existence of symlink
	exists = lstat("outfile", &stats);
	//printf("%d %lo", stats.st_mode, stats.st_mode);
	//if(exists == 0 && stats.st_mode == 41471) {
	if((stats.st_mode & S_IFMT) == S_IFLNK) {
		wstdout("Checking whether the symlink has been created: Yes");
	}
	else{
		wstdout("Checking whether the symlink has been created: No");
	}


	wstdout("");
	permission_lena_chahiye_na("Assignment/outfile", "file");
	wstdout("");
	permission_lena_chahiye_na("Assignment", "directory");
	wstdout("");
	permission_lena_chahiye_na("outfile", "symlink");

	return 0;
}

void integrityCheck() {
	
}

void permission_lena_chahiye_na(char path[], char name[]) {
	struct stat stats;
	lstat(path, &stats);



	if(stats.st_mode & S_IRUSR) {
		if(len(name) == 4) {
			wstdout("User has read permission on file: Yes");
		}
		else if(len(name) == 7) {
			wstdout("User has read permission on symlink: Yes");
		}
		else {
			wstdout("User has read permission on directory: Yes");
		}
	}
	else {
		if(len(name) == 4) {
			wstdout("User has read permission on file: No");
		}
		else if(len(name) == 7) {
			wstdout("User has read permission on symlink: No");
		}
		else {
			wstdout("User has read permission on directory: No");
		}
	}

	if(stats.st_mode & S_IWUSR) {
		if(len(name) == 4) {
			wstdout("User has write permission on file: Yes");
		}
		else if(len(name) == 7) {
			wstdout("User has write permission on symlink: Yes");
		}
		else {
			wstdout("User has write permission on directory: Yes");
		}
	}
	else {
		if(len(name) == 4) {
			wstdout("User has write permission on file: No");
		}
		else if(len(name) == 7) {
			wstdout("User has write permission on symlink: No");
		}
		else {
			wstdout("User has write permission on directory: No");
		}
	}

	if(stats.st_mode & S_IXUSR) {
		if(len(name) == 4) {
			wstdout("User has execute permission on file: Yes");
		}
		else if(len(name) == 7) {
			wstdout("User has execute permission on symlink: Yes");
		}
		else {
			wstdout("User has execute permission on directory: Yes");
		}
	}
	else {
		if(len(name) == 4) {
			wstdout("User has execute permission on file: No");
		}
		else if(len(name) == 7) {
			wstdout("User has execute permission on symlink: No");
		}
		else {
			wstdout("User has execute permission on directory: No");
		}
	}
	wstdout("");





	if(stats.st_mode & S_IRGRP) {
		if(len(name) == 4) {
			wstdout("Group has read permission on file: Yes");
		}
		else if(len(name) == 7) {
			wstdout("Group has read permission on symlink: Yes");
		}
		else {
			wstdout("Group has read permission on directory: Yes");
		}
	}
	else {
		if(len(name) == 4) {
			wstdout("Group has read permission on file: No");
		}
		else if(len(name) == 7) {
			wstdout("Group has read permission on symlink: No");
		}
		else {
			wstdout("Group has read permission on directory: No");
		}
	}

	if(stats.st_mode & S_IWGRP) {
		if(len(name) == 4) {
			wstdout("Group has write permission on file: Yes");
		}
		else if(len(name) == 7) {
			wstdout("Group has write permission on symlink: Yes");
		}
		else {
			wstdout("Group has write permission on directory: Yes");
		}
	}
	else {
		if(len(name) == 4) {
			wstdout("Group has write permission on file: No");
		}
		else if(len(name) == 7) {
			wstdout("Group has write permission on symlink: No");
		}
		else {
			wstdout("Group has write permission on directory: No");
		}
	}

	if(stats.st_mode & S_IXGRP) {
		if(len(name) == 4) {
			wstdout("Group has execute permission on file: Yes");
		}
		else if(len(name) == 7) {
			wstdout("Group has execute permission on symlink: Yes");
		}
		else {
			wstdout("Group has execute permission on directory: Yes");
		}
	}
	else {
		if(len(name) == 4) {
			wstdout("Group has execute permission on file: No");
		}
		else if(len(name) == 7) {
			wstdout("Group has execute permission on symlink: No");
		}
		else {
			wstdout("Group has execute permission on directory: No");
		}
	}
	wstdout("");




	if(stats.st_mode & S_IROTH) {
		if(len(name) == 4) {
			wstdout("Others has read permission on file: Yes");
		}
		else if(len(name) == 7) {
			wstdout("Others has read permission on symlink: Yes");
		}
		else {
			wstdout("Others has read permission on directory: Yes");
		}
	}
	else {
		if(len(name) == 4) {
			wstdout("Others has read permission on file: No");
		}
		else if(len(name) == 7) {
			wstdout("Others has read permission on symlink: No");
		}
		else {
			wstdout("Others has read permission on directory: No");
		}
	}

	if(stats.st_mode & S_IWOTH) {
		if(len(name) == 4) {
			wstdout("Others has write permission on file: Yes");
		}
		else if(len(name) == 7) {
			wstdout("Others has write permission on symlink: Yes");
		}
		else {
			wstdout("Others has write permission on directory: Yes");
		}
	}
	else {
		if(len(name) == 4) {
			wstdout("Others has write permission on file: No");
		}
		else if(len(name) == 7) {
			wstdout("Others has write permission on symlink: No");
		}
		else {
			wstdout("Others has write permission on directory: No");
		}
	}

	if(stats.st_mode & S_IXOTH) {
		if(len(name) == 4) {
			wstdout("Others has execute permission on file: Yes");
		}
		else if(len(name) == 7) {
			wstdout("Others has execute permission on symlink: Yes");
		}
		else {
			wstdout("Others has execute permission on directory: Yes");
		}
	}
	else {
		if(len(name) == 4) {
			wstdout("Others has execute permission on file: No");
		}
		else if(len(name) == 7) {
			wstdout("Others has execute permission on symlink: No");
		}
		else {
			wstdout("Others has execute permission on directory: No");
		}
	}
	wstdout("");





}
