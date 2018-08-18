#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>

#define MAX_BUFF 1048576

void permission_lena_chahiye_na(char*, char*);
void integrityCheck(char*);

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

int main(int argc, char *argv[]){

	if(argc != 2) {
		wstdout("Usage: ./a.out filename(of original input file)");
		exit(1);
	}

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

	integrityCheck(argv[1]);

	wstdout("");
	permission_lena_chahiye_na("Assignment/outfile", "file");
	wstdout("");
	permission_lena_chahiye_na("Assignment", "directory");
	wstdout("");
	permission_lena_chahiye_na("outfile", "symlink");

	return 0;
}

void integrityCheck(char str[]) {
	char buffer[MAX_BUFF];
	char rbuf[MAX_BUFF];

	int fd_converted = open("Assignment/outfile", O_RDONLY);
	int fd_original = open(str, O_RDONLY);

	//wstdout("trying");






	int seek = lseek(fd_converted, 0, SEEK_END);
	//printf("%d", seek>MAX_BUFF);
	int flag = 1;
	// When file > MAX_BUFF
	while(seek > MAX_BUFF) {
	//	wstdout("bigger than buffer");
		// Navigate pointer to required
		seek = lseek(fd_converted, seek-MAX_BUFF, SEEK_SET);

		// Read MAX_BUFF chars into the buffer
		read(fd_converted, buffer, MAX_BUFF);
		read(fd_original, rbuf, MAX_BUFF);

		// Reverse the buffer into rbuf
		for(int i = 0; i < MAX_BUFF; i++) {
			if(buffer[i] >= 'A' && buffer[i] <= 'Z') {
				buffer[i] += 32;
			}
			else if(buffer[i] >= 'a' && buffer[i] <= 'z') {
				buffer[i] -= 32;
			}

			if(buffer[i] != rbuf[MAX_BUFF - 1 - i]) {
				wstdout("Checking whether file contents have been reversed and case-inverted: No");
				flag = 0;
				break;
			}
		}
	}
	if(flag == 1) {
	//	wstdout("within buffer");
		size_t buff = seek;
		seek = lseek(fd_converted, 0, SEEK_SET);
		read(fd_converted, buffer, buff);
		read(fd_original, rbuf, buff);
		for(int i = 0; i < buff; i++) {
			if(buffer[i] >= 'A' && buffer[i] <= 'Z') {
				buffer[i] += 32;
			}
			else if(buffer[i] >= 'a' && buffer[i] <= 'z') {
				buffer[i] -= 32;
			}
			if(rbuf[buff - 1 - i] != buffer[i]) {
				wstdout("Checking whether file contents have been reversed and case-inverted: No");
				flag = 0;
				break;
			}
		}
	}
	if(flag == 1) {
		wstdout("Checking whether file contents have been reversed and case-inverted: Yes");
	}

	











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
