#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
using namespace std;

#define LEN 1234
#define PORT 1234

int read_from_socket(int, char *, int);

int main(int argc, char ** argv) {
	char buf[LEN];
	FILE * fp = stdin;

	if (argc > 1 && !(fp = fopen(argv[1], "r"))) {
		perror("fopen() error");
		return 1;
	}

	struct sockaddr_in addr;
	int sock = 0;
	int opt = 1;
	int len = 0;
	int res = 0;

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		perror("socket() error");
		return 1;
	}
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
//	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_aton("127.0.0.1", &addr.sin_addr);
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		perror("connect error");
		close(sock);
		return 2;
	}

	while (fgets(buf, LEN, fp)) {
		len = strlen(buf);
		write(sock, &len, sizeof(int));
		write(sock, buf, len);
		while ((res = read_from_socket(sock, buf, LEN)) > 0) {
			write(STDOUT_FILENO, buf, res);
		}
		if (res < 0) break;
	}

	close(sock);
	return 0;
}

int read_from_socket(int fd, char * buf, int len) {
	if (read(fd, &len, sizeof(int)) != (int)sizeof(int)) {
		perror("read_from_socket() read_length error");
		return -1;
	}
//printf("# %d\n", len);
	int l = len;
	int i = 0;
	int nbytes = 0;
	for (i = 0; len > 0; i += nbytes, len -= nbytes) {
		nbytes = read(fd, buf + i, len);
		if (nbytes < 0) {
			perror("read_from_socket() read() error");
			return -1;
		} else if (nbytes == 0) {
			perror("read truncated");
			return -1;
		}
	}
	buf[i] = 0;
//	printf("read\n\tbytes: %d\n\t_msg_: %s\n\t_len_: %d\n", i, (i > 0) ? buf : "empty", l);
	return l;
}

