#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char* argv[]) {
	int fcPipe[2];
	int buffer[1024];
	pid_t pid;
	char* initialFile = argv[1];
	char* copiedFile = argv[2];
	pipe(fcPipe);
	pid = fork();
	if (pid > 0) {
		close(fcPipe[0]);
		int inFile = open(initialFile, O_RDONLY);
		ssize_t bytes = read(inFile, buffer, sizeof(buffer));
		write(fcPipe[1], buffer, bytes);
		close(fcPipe[1]);
	}
	else if (pid == 0) {
		close(fcPipe[1]);
		ssize_t bytes = read(fcPipe[0], buffer, sizeof(buffer));
		close(fcPipe[0]);
		int cpFile = open(copiedFile, O_CREAT | O_WRONLY);
		write(cpFile, buffer, bytes);
	}
}
