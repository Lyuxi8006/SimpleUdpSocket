#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
	char buffer[64] = {0};
	struct sockaddr_in server_addr = {0};
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1)
	{
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(12345);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	int rc = bind(sockfd, (const struct sockaddr *)&server_addr,
			sizeof(server_addr));
	if (rc == -1)
	{
		perror("failed to bind");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	socklen_t len = 0;
	int n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL, 0, &len);

	printf("%s", buffer);
	close(sockfd);
	return 0;
}








