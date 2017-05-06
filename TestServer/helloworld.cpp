#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
	int sockfd, newsockfd;

	struct sockaddr_in serv_addr, cli_addr;

	socklen_t clilen;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	char buffer[256];
	bzero(buffer, 256);

	if (sockfd < 0) {
		fprintf(stderr, "Error opening socket.\n");
		exit(1);
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(8001);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		fprintf(stderr, "Error on binding.\n");
		exit(1);
	}

	listen(sockfd, 5);

	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd < 0) {
		fprintf(stderr, "Error on accept.\n");
		exit(1);
	}

	while (strcmp(buffer, "Exit\n") != 0) {
		int n = write(newsockfd, "A test phrase\n", 14);

		if (n < 0) {
			fprintf(stderr, "Error writing to socket.\n");
			exit(1);
		}

		bzero(buffer, 256);
		n = read(newsockfd, buffer, 255);

		if (n < 0) {
			fprintf(stderr, "Error reading from socket.\n");
			exit(1);
		}

		printf("%s", buffer);
	}

	int n = write(newsockfd, "Exit\n", 6);

	if (n < 0) {
		fprintf(stderr, "Error writing to socket.\n");
		exit(1);
	}

	close(newsockfd);
	close(sockfd);

	return 0;
}