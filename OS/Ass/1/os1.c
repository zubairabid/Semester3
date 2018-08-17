#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>

#define MAX_BUFF 4096

int wstdout(char str[]) {
	write(1, str, sizeof(str));
	write(1, "\n", 1);
}

int main(int argc, char *argv[]) {

	if (argc != 2) {
		wstdout("Usage: ./a.out filename");
		exit(1);
	}

	char buffer[MAX_BUFF];
	char rbuf[MAX_BUFF];

	// Opening input file
	int fd_input = open(argv[1], O_RDONLY);
	if(fd_input == -1) {
		wstdout("Could not open input text file");
		exit(1);
	}

	// Create output directory
	int dir = mkdir("Assignment", S_IRWXU);
	if(dir) {
		wstdout("Could not create directory");
		exit(1);
	}

	// Create output file
	int fd_out = creat("Assignment/outfile", S_IRWXU);
	if(fd_out == -1) {
		wstdout("Could not create output text file");
		exit(1);
	}
	
	int seek = lseek(fd_input, 0, SEEK_END);

	// When file > MAX_BUFF
	while(seek > MAX_BUFF) {
		// Navigate pointer to required
		seek = lseek(fd_input, seek-MAX_BUFF, SEEK_SET);
		
		// Read MAX_BUFF chars into the buffer
		read(fd_input, buffer, MAX_BUFF);
		
		// Reverse the buffer into rbuf
		for(int i = 0; i < MAX_BUFF; i++) {
			if(buffer[i] >= 'A' && buffer[i] <= 'Z') {
				buffer[i] += 32;
			}
			else if(buffer[i] >= 'a' && buffer[i] <= 'z') {
				buffer[i] -= 32;
			}
			rbuf[MAX_BUFF - 1 - i] = buffer[i];
		}
		write(fd_out, rbuf, MAX_BUFF);
	}

	// Countering the else condition to that:
	size_t buff = seek;
	seek = lseek(fd_input, 0, SEEK_SET);
	read(fd_input, buffer, buff);

	for(int i = 0; i < buff; i++) {
		if(buffer[i] >= 'A' && buffer[i] <= 'Z') {
			buffer[i] += 32;
		}
		else if(buffer[i] >= 'a' && buffer[i] <= 'z') {
			buffer[i] -= 32;
		}
		rbuf[buff - 1 - i] = buffer[i];
	}
	write(fd_out, rbuf, buff);
	wstdout("File written into Assignment/outfile");

	return 0;
}
